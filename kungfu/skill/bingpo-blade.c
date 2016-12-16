// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;


string *action_msg = ({
        "$N�ḧ���е�$w��ͻȻ��ֻ������һ������������һ���������̹ǵĺ�����ȻϮ����$n��$l",
        "ֻ��$N����$w�����μ��壬������$n����֮�ʣ�ͻȻ����һ����$n����б������",
        "$Nб�����𣬴���һƬƥ��Ҳ�Ƶĵ������$n��$l",
        "$NͻȻһ���߳������е�$w����һ�������Բ���������ĵ����ס��$n��ͷ�����ж���$n�ĺ���",
        "ֻ��$N��ɫһ����һ�С�ǧ����⡹ʹ������ü�ݵ��Ÿ���\n$n������ѪҺ���Ʊ����޾��ĵ��ƶ�ס��������Ҳ�·�Ҫ�����ȥ",
        "$N���ƽ�������$w�ϴ����ĺ���ȴԽ��ԽŨ��������ʱ��\n$n����ͷһ����һ������⻹Ҫ�����ĺ����Ѵ�����$n$l",
        "$NҲ�������߶�ʮһ���߾�$w�����ؾ���һ����$nӭ��ն�£�\n��Ȼֻ��һ�������µĵ���ȴ����Ų����ĺ���������$n��һ����·",
});


int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<100 )
                return notify_fail("�������������û�а취�����Ǻ���������Щ���������ɡ�\n");

        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "blade"
         || query("material", ob) != "ice" )
                return notify_fail("���������һ�ѱ����ĵ����������Ǻ�����\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 260 + random(30),
                "dodge" : -60 + random(10),
                "parry" : -60 + random(10),
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<110
             || query("neili", me)<110 )
                return notify_fail("�����������������û�а취��ϰ���Ǻ�����\n");

        me->receive_damage("qi", 100);
        addn("neili", -100, me);
        write("�㰴����ѧ����һ����Ǻ�����\n");
        return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon=query_temp("weapon", me);
        string msg;

        if (( damage_bonus > 250 ) && (! userp(me)))
                return 0;

        if (((int)me->query_skill("blade", 1)/2) > random((int)victim->query_skill("force", 1)))
        {
                victim->receive_wound("qi", (300-damage_bonus));
                msg = HIW "$NĬ�������������Ǻ����к����Ƴ���$nһ�����죬�ѱ����ˣ�\n\n"NOR;
                message_combatd(msg, me, victim);

        }
        switch(random(3)) {
        case 0:
                victim->receive_damage("qi",damage_bonus/3*2);
                msg = "ֻ��һ˿����������Ϣ���굽$n���ڣ�\n";
                break;

        case 1:
                victim->receive_damage("qi",damage_bonus/2);
                msg = "$N��ʹ��������$n���˿�������һ��ǳǳ�İ�ӡ��\n";
                break;

        case 2:
                victim->receive_damage("qi",damage_bonus);
                msg = "$nͻȻ���������溮����...\n";
                break;
        }

        return msg;
}
string perform_action_file(string action)
{
        return __DIR__"bingpo-blade/" + action;

}

