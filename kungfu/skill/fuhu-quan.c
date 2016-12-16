// /lungfu/skill/fuhu-quan
// by dubei
// �޺�����ȭ

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action" : "$N����˫ȭ��ʹ��һ�С��ඥ������ͷ����$n��$l  ",
        "skill_name" : "�ඥ",
        "force" : 80,
        "dodge" : 5,
        "lvl" : 0,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С���ࡹ������һ�ͣ����ֻ���������һȭ����$n���ɲ�  ",
        "skill_name" : "���",
        "force" : 60,
        "dodge" : -5,
        "lvl" : 10,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С��ü������ȭ���$n��ǰ�أ�һ��������ȭ��ɨ$n��̫��Ѩ  ",
        "skill_name" : "�ü",
        "force" : 80,
        "dodge" : 10,
        "lvl" : 20,
        "damage_type" : "����",
]),
([      "action" : "$N���ι��죬ʹһ�С���������˫ȭ���»���$n��$l  ",
        "skill_name" : "����",
        "force" : 100,
        "dodge" : 5,
        "lvl" : 40,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����š���˫ȭ��������������������ֱָ$n��$l  ",
        "skill_name" : "����",
        "force" : 120,
        "dodge" : -5,
        "lvl" : 50,
        "damage_type" : "����",
]),
([      "action" : "$N΢΢һЦ��ʹ��һʽ����������˫ȭǰ�������ֱȡ$n������  ",
        "skill_name" : "����",
        "force" : 150,
        "dodge" : 10,
        "lvl" : 60,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����ġ���ȫ����ת��˫ȭ��ɨ$n��$l  ",
        "skill_name" : "����",
        "force" : 270,
        "dodge" : 20,
        "lvl" : 80,
        "damage_type" : "����",
]),
([      "action" : "$N����һԾ��ʹ��һ�С���ʤ����һȭ�ͻ�$n�ʺ�  ",
        "skill_name" : "��ʤ",
        "force" : 260,
        "dodge" : 5,
        "lvl" : 100,
        "damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("���޺�����ȭ������֡�\n");
    else if( query("max_neili", me)<1000 )
                return notify_fail("��������������޺�����ȭ��\n");
    if ((int)me->query_skill("hunyuan-yiqi", 1) < 100 )
                      return notify_fail("�����������Ԫ�������������������޺�����ȭ��\n");
 
        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("fuhu-quan", 1))
                      return notify_fail("��Ļ���ȭ����򣬻��������޺�����ȭ��\n");
          return 1;
}
 int valid_combine(string combo)
 {
         object me;
         me = this_player();
 
         if ((int)me->query_str() > 32)
                 return combo=="qinlong-shou";
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
          level = (int)me->query_skill("fuhu-quan", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
            if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("���޺�����ȭ������֡�\n");
         if( query("jingli", me)<30 )
                 return notify_fail("�������̫���ˡ�\n");
         if( query("neili", me)<20 )
                 return notify_fail("��������������޺�����ȭ��\n");
         addn("jingli", -25, me);
         addn("neili", -5, me);
         return 1;
}
