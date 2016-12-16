inherit SKILL;

int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<500 )
                return notify_fail("�������������û�а취����ɳ��Ӱ��\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹���û�а취����ɳ��Ӱ��\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("hansha-sheying", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������ĺ�ɳ��Ӱ��\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "throwing";
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("�����������û�а취��ϰ��ɳ��Ӱ��\n");

        if( query("neili", me)<50 )
                return notify_fail("�������������û�а취��ϰ��ɳ��Ӱ��\n");

        me->receive_damage("qi", 35);
        addn("neili", -48, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"hansha-sheying/" + action;
}