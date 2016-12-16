#include <ansi.h>
// 仁王经 renwang-jing
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "段氏皇族"; }

int valid_learn(object me)
{        
        if (me->query_skill("sun-finger", 1) < 30)
                return notify_fail("你一阳指火候不足，无法研习仁王经。\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("仁王经只能段氏皇族弟子方可研习。\n");

        if (me->query_skill("kurong-changong", 1) < 
            me->query_skill("renwang-jing", 1) * 60 /100)
                return notify_fail("你枯荣禅功修为不足，无法继续研习仁王经。\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
