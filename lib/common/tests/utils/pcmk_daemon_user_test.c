/*
 * Copyright 2022 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>
#include "mock_private.h"

#include <pwd.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sys/types.h>

int
__wrap_getpwnam_r(const char *name, struct passwd *pwd, char *buf, size_t buflen,
                  struct passwd **result)
{
    *result = mock_ptr_type(struct passwd *);
    return 0;
}

static void
no_matching_pwent(void **state)
{
    uid_t uid;
    gid_t gid;

    will_return(__wrap_getpwnam_r, NULL);               // result parameter to getpwnam_r()

    assert_int_equal(pcmk_daemon_user(&uid, &gid), -EINVAL);
}

static void
entry_found(void **state)
{
    uid_t uid;
    gid_t gid;

    /* We don't care about any of the other fields of the password entry, so just
     * leave them blank.
     */
    struct passwd returned_ent = { .pw_uid = 1000, .pw_gid = 1000 };

    /* Test getpwnam_r returning a valid passwd entry, but we don't pass uid or gid. */

    will_return_always(__wrap_getpwnam_r, &returned_ent);      // result parameter to getpwnam_r()

    assert_int_equal(pcmk_daemon_user(NULL, NULL), 0);

    /* Test getpwnam_r returning a valid passwd entry, and we do pass uid and gid. */

    assert_int_equal(pcmk_daemon_user(&uid, &gid), 0);
    assert_int_equal(uid, 1000);
    assert_int_equal(gid, 1000);
}

int main(int argc, char **argv)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(no_matching_pwent),
        cmocka_unit_test(entry_found),
    };

    cmocka_set_message_output(CM_OUTPUT_TAP);
    return cmocka_run_group_tests(tests, NULL, NULL);
}