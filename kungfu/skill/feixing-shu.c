// feixing-shu.c 飞星术
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *dodge_msg = ({
        "$n左一点右一晃，随即回到原地，轻巧地躲过了$N这一招。\n",
        "$n腾身跃起一个空翻，并顺势闪到一边。\n",
        "$n轻轻往旁边一纵，就已离$N有了相当的距离，$N这一招自然失效。\n",
        "$n揉身而上，轻灵地跃过$N，闪到了$N的背后。\n",
        "$n身形急闪，斜向前一步，竟然已经躲开了$N的这一招。\n",
        "$N眼前一花，却见$n竟然已离自己有数丈之远，却没见$n如何躲过自己的攻击的�
n",
        "$N一个不留神，$n已没了踪影。$N急转身，却见$n在那儿向自己招手。\n",
        "$N一招攻出，$n已然不见，$N茫然四顾，却不见$n的影子！\n",
});

mapping *action = ({
([        "action" : "$N轻身而退，一招『初露星芒』，手中$w化作一点寒芒射向$n",
        "damage": 130,
        "dodge" : 40,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 0,
        "skill_name" : "初露星芒"
]),
([        "action" : "$N右手微向前一伸，使出『乍见星辰』，手里$w径直射向$n的双眼",
        "damage": 40,
        "dodge" : 45,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 9,
        "skill_name" : "乍见星辰"
]),
([        "action" : "$N一声轻啸，施展出『寒夜孤星』，身形微动，手中$w竟然向上飞\n起绕了个圈，随而迅速袭向$n的腰间",
        "damage": 50,
        "dodge" : 40,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 18,
        "skill_name" : "寒夜孤星"
]),
([        "action" : "$N使一招『星光闪烁』，突然纵身向后一个翻滚，就在快落地的一瞬间，$n陡然发现几点寒光闪烁不定地袭向自己",
        "damage": 135,
        "dodge" : 55,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "扎伤",
        "lvl" : 27,
        "skill_name" : "星光闪烁"
]),
([        "action" : "$N右手一挥，一招『星芒不定』，$n明明看见$N手里的$w已射向自己的胸前大穴，到了近处却突然转攻向自己的后心",
        "damage": 160,
        "dodge" : 50,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 36,
        "skill_name" : "星芒不定"
]),
([        "action" : "$N不急不缓地一矮身，使出『坠落之星』，手中$w平直地射向$n的咽喉，却又加上暗劲使之中途改向，射向$n的下盘",
        "damage": 140,
        "dodge" : 54,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 45,
        "skill_name" : "坠落之星"
]),
([        "action" : "$N腾身一跃而起，施展出『黎明之星』，手里的$w从上往下笔直地射向$n的头部",
        "damage": 85,
        "dodge" : 10,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 54,
        "skill_name" : "黎明之星"
]),
([        "action" : "$N原地一个急转身，随即双手一拂，$w就飘飘忽忽地飞向$n，原来这招是『星辰游离』",
        "force":40,
        "damage": 110,
        "dodge" : 55,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 63,
        "skill_name" : "星辰游离"
]),
([        "action" : "$N使出一招『星光顿灭』，前脚一跺，随即翻身而起，手中$w不带丝毫风声却又迅速无比地射向$n的前胸",
        "force":63,
        "damage": 120,
        "dodge" : 60,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 72,
        "skill_name" : "星光顿灭"
]),
([        "action" : "$N突然腾身向后急退，使出『星空炸雷』，双手向前一推，手里$w就隐隐带着雷声疾射向$n",
        "force":70,
        "damage": 110,
        "dodge" : -5,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 81,
        "skill_name" : "星空炸雷"
]),
([        "action" : "$N施展出『"+HIW"星划长空"NOR+"』，原地侧身飞起，右手微微向前一洒，手中$w幻作一点寒光呈圆弧形射向$n",
        "force":90,
        "damage": 160,
        "dodge" : 50,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 90,
        "skill_name" : "星划长空"
]),
([        "action" : "$N微微凝神，使出『"+HIY"星光万丈"NOR+"』，身影飘忽不定，$n顿觉十分刺眼，却见$N手里的$w已挟着地上的沙石以及周围的树页攻向自己",
        "force":100,
        "damage": 130,
        "dodge" : 65,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 99,
        "skill_name" : "星光万丈"
]),
([        "action" : "$N忽然轻叹一声，转身而行，$n正迟疑间，却见眼前已尽是$w的影子，眼看无处可躲了！只怕这招就是『"+HIC"满天星雨"NOR+"』了，$n不由大惊失色",
        "force": 88,
        "damage": 120,
        "dodge" : 70,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺伤",
        "lvl" : 110,
        "skill_name" : "满天星雨"
])
});

int valid_enable(string usage)
{
        return usage=="throwing" || usage=="dodge" || usage=="parry" || usage=="move";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功心法火候不够，无法学飞星术。\n");

        if ((int)me->query_skill("dodge") < 40)
                return notify_fail("你的轻功火候不够，无法学习飞星术。\n");

        if ((int)me->query_skill("poison", 1) < 30)
                return notify_fail("你的毒功火候不够，无法领悟飞星术。\n");

        if ((int)me->query_dex() < 25)
                return notify_fail("你的身法不够灵巧，无法学习飞星术。\n");

/*
        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("feixing-shu", 1))
                return notify_fail("你的基本暗器水平有限，无法领悟更高深的飞星术。\n");
*/

        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<30 )
                return notify_fail("你的内力不够练飞星术。\n");
        me->receive_damage("qi", 30);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
                return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("feixing-shu", 1);
        for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/5)];
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int learn_bonus() { return 10; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"feixing-shu/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( random(me->query_skill("poison",1)) > 20)
        {
                victim->apply_condition("xx_poison", random(2) + 1 + victim->query_condition("xx_poison"));
        }
}

int help(object me)
{
        write(HIC"\n飞星术："NOR"\n");
        write(@HELP

    飞星术是星宿派暗器。

        学习要求：
                化功大法20级
                基本轻功20级
                后天身法25
HELP
        );
        return 1;
}
