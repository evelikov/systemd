/* SPDX-License-Identifier: LGPL-2.1+ */
/***
  This file is part of systemd.

  Copyright 2011 Lennart Poettering
***/

#include "alloc-util.h"
#include "journald-syslog.h"
#include "macro.h"
#include "string-util.h"

static void test_syslog_parse_identifier(const char* str,
                                         const char *ident, const char*pid, int ret) {
        const char *buf = str;
        _cleanup_free_ char *ident2 = NULL, *pid2 = NULL;
        int ret2;

        ret2 = syslog_parse_identifier(&buf, &ident2, &pid2);

        assert_se(ret == ret2);
        assert_se(ident == ident2 || streq_ptr(ident, ident2));
        assert_se(pid == pid2 || streq_ptr(pid, pid2));
}

int main(void) {
        test_syslog_parse_identifier("pidu[111]: xxx", "pidu", "111", 11);
        test_syslog_parse_identifier("pidu: xxx", "pidu", NULL, 6);
        test_syslog_parse_identifier("pidu xxx", NULL, NULL, 0);

        return 0;
}
