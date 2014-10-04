// if s1 starts with s2 returns true, else false
// len is the length of s1
// s2 should be null-terminated
static bool starts_with(const char *s1, int len, const char *s2)
{
	int n = 0;
	while (*s2 && n < len) {
		if (*s1++ != *s2++)
			return false;
		n++;
	}
	return *s2 == 0;
}

// convert escape sequence to event, and return consumed bytes on success (failure == 0)
static int parse_escape_seq(struct tb_event *event, const char *buf, int len)
{
	// it's pretty simple here, find 'starts_with' match and return
	// success, else return failure
	int i;
	for (i = 0; keys[i]; i++) {
		if (starts_with(buf, len, keys[i])) {
			event->ch = 0;
			event->key = 0xFFFF-i;
			return strlen(keys[i]);
		}
	}
	return 0;
}

static bool extract_event(struct tb_event *event, struct bytebuffer *inbuf, int inputmode)
{
	const char *buf = inbuf->buf;
	const int len = inbuf->len;
	if (len == 0)
		return false;

	if (buf[0] == '\033') {
		int n = parse_escape_seq(event, buf, len);
		if (n) {
			bytebuffer_truncate(inbuf, n);
			return true;
		} else {
			// it's not escape sequence, then it's ALT or ESC,
			// check inputmode
			switch (inputmode) {
			case TB_INPUT_ESC:
				// if we're in escape mode, fill ESC event, pop
				// buffer, return success
				event->ch = 0;
				event->key = TB_KEY_ESC;
				event->mod = 0;
				bytebuffer_truncate(inbuf, 1);
				return true;
			case TB_INPUT_ALT:
				// if we're in alt mode, set ALT modifier to
				// event and redo parsing
				event->mod = TB_MOD_ALT;
				bytebuffer_truncate(inbuf, 1);
				return extract_event(event, inbuf, inputmode);
			default:
				assert(!"never got here");
				break;
			}
		}
	}

	// if we're here, this is not an escape sequence and not an alt sequence
	// so, it's a FUNCTIONAL KEY or a UNICODE character

	// first of all check if it's a functional key
	if ((unsigned char)buf[0] <= TB_KEY_SPACE ||
	    (unsigned char)buf[0] == TB_KEY_BACKSPACE2)
	{
		// fill event, pop buffer, return success */
		event->ch = 0;
		event->key = (uint16_t)buf[0];
		bytebuffer_truncate(inbuf, 1);
		return true;
	}

	// feh... we got utf8 here

	// check if there is all bytes
	if (len >= tb_utf8_char_length(buf[0])) {
		/* everything ok, fill event, pop buffer, return success */
		tb_utf8_char_to_unicode(&event->ch, buf);
		event->key = 0;
		bytebuffer_truncate(inbuf, tb_utf8_char_length(buf[0]));
		return true;
	}

	// event isn't recognized, perhaps there is not enough bytes in utf8
	// sequence
	return false;
}
