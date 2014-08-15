#include "sandboxprocess.h"
#include <fcntl.h>
#include <seccomp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/prctl.h>

#include <sys/time.h>
#include <sys/resource.h>


SandBoxProcess::SandBoxProcess(QObject *parent) :
    QProcess(parent)
{
}

void SandBoxProcess::setupChildProcess()
{
    // seccomp
    {
        scmp_filter_ctx ctx;
        ctx = seccomp_init(SCMP_ACT_ALLOW);

        seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(fork), 0);
        //seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(clone), 0);

        prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);

        seccomp_load(ctx);
        seccomp_release(ctx);
    }
    // rlimit
    {
        struct rlimit limit;
        int r;
        limit.rlim_cur = 1024 * 1024 * 1024;limit.rlim_max = 1024 * 1024 * 1024;
        r = setrlimit(RLIMIT_DATA, &limit);

        struct rlimit as;
        as.rlim_max = 1024 * 1024 * 1024;as.rlim_cur = 1024 * 1024 * 1024;
        r = setrlimit(RLIMIT_AS, &as);

    }

}
