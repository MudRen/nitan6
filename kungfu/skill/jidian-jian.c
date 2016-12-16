#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N����Ծ������$w��ӣ�һ�С���ƽ�˾�����ն��$n��",
        "force"  : 80,
        "attack" : 35,
        "parry"  : 10,
        "dodge"  : 30,
        "damage" : 75,
        "lvl"    : 0,
        "skill_name" : "��ƽ�˾�",
        "damage_type" : "����"
]),
([      "action" : "$N����$w�����������Σ�һ�С�������ӿ������$n���ұ����ն��",
        "force"  : 100,
        "attack" : 45,
        "parry"  : 22,
        "dodge"  : 45,
        "damage" : 88,
        "lvl"    : 30,
        "skill_name" : "������ӿ",
        "damage_type" : "����"
]),
([      "action" : "$N����һ��������һԾ����һ�С�������ơ���������$n�̳�����",
        "force"  : 120,
        "attack" : 51,
        "parry"  : 18,
        "dodge"  : 53,
        "damage" : 95,
        "lvl"    : 60,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$N����һ����Х��б����ǰ��һ�С�������ɢ����$w����ֱ��������$n��$l",
        "force"  : 150,
        "attack" : 58,
        "parry"  : 20,
        "dodge"  : 52,
        "damage" : 110,
        "lvl"    : 90,
        "skill_name" : "������ɢ",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("��������������޷���ϰ���罣����\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("����Ṧ���̫ǳ���޷���ϰ���罣����\n");

        if ((int)me->query_dex() < 25)
                return notify_fail("����������������޷���ϰ���罣����\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jidian-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������ļ��罣����\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int) me->query_skill("jidian-jian",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<65 )
                return notify_fail("����������������罣����\n");

        if( query("neili", me)<20 )
                return notify_fail("����������������罣����\n");

        me->receive_damage("qi", 60);
        addn("neili", -16, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jidian-jian/" + action;
}