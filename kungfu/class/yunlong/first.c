#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("yunlong")+"/chen");
        set("start_room","/d/beijing/qingmu_dating");
        ::create();
}

string zm_apply()
{
        return ::zm_apply();
}
