#include <ansi.h>

inherit SKILL;

int valid_learn(object me)
{
        object ob;
  
        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("你的暗器技能不够娴熟。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("bagua-biao", 1))
                return notify_fail("你的基本暗器水平有限，难以领会更精妙的八卦镖诀。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "throwing";
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的气不够，没有办法练习八卦镖诀。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的内力不够，没有办法练习八卦镖诀。\n");

        me->receive_damage("qi", 70);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"bagua-biao/" + action;
}