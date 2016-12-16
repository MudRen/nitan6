inherit SKILL;

mapping *action = ({
([      "action": "$N����$wбָ��һ�С�ŭ����ԭ��������һ�٣�һ����$n��$l��ȥ",
        "force" : 20,
        "dodge" : 10,
        "parry" : 25,
        "damage": 5,
        "lvl"   : 0,
        "skill_name"  : "ŭ����ԭ",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С�������졹����������㣬$wһ��һ�գ�ƽ�л���$n�ľ���",
        "force" : 30,
        "dodge" : 30,
        "parry" : 40,
        "damage": 10,
        "lvl"   : 20,
        "skill_name"  : "�������",
        "damage_type" : "����"
]),
([      "action": "$Nչ���鲽������Ծ�䣬һ�С���¯���ڡ�������һ��������ն��$n",
        "force" : 40,
        "dodge" : 35,
        "parry" : 45,
        "damage": 15,
        "lvl"   : 40,
        "skill_name"  : "��¯����",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С����Ƿ�׹����$w�󿪴��أ����϶��»���һ���󻡣���ֱ����$n",
        "force" : 60,
        "dodge" : 45,
        "parry" : 45,
        "damage": 20,
        "lvl"   : 60,
        "skill_name"  : "���Ƿ�׹",
        "damage_type" : "����"
]),
([      "action": "$N����$wһ����һ�С��������졹��˫�ֳ����������У�����$n���ؿ�",
        "force" : 80,
        "dodge" : 50,
        "parry" : 55,
        "damage": 25,
        "lvl"   : 80,
        "skill_name"  : "��������",
        "damage_type" : "����"
]),
([      "action": "$N����$w��ʹ��һ�С��������������������ã����ҿ�����������$n",
        "force" : 90,
        "dodge" : 65,
        "parry" : 55,
        "damage": 30,
        "lvl"   : 100,
        "skill_name"  : "��������",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С������һ𡹣����Ծ����أ�$w˳����ǰ��Ю��������$n��$l",
        "force" : 120,
        "dodge" : 75,
        "parry" : 85,
        "damage": 35,
        "lvl"   : 120,
        "skill_name"  : "�����һ�",
        "damage_type" : "����"
]),
([      "action": "$N����פ�أ�һ�С��������������ӳ�һƬ�����ĵ�Ӱ����$n��ȫ��ӿȥ",
        "force" : 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 40,
        "lvl"   : 140,
        "skill_name"  : "��������",
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("���������Ϊ������\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("honglian-dao", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������ĺ���������\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("honglian-dao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<60 )
                return notify_fail("�����������������������\n");

        if( query("neili", me)<60 )
                return notify_fail("�����������������������\n");

        me->receive_damage("qi", 45);
        addn("neili", -43, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"honglian-dao/" + action;
}