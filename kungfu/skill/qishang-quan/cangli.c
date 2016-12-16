// cangli.c �����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�����"; }

int perform(object me)
{
        string msg,str;
        object target;
        int skill, neili_wound;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("���������ֻ����ս����ʹ�á�\n");

        if( (int)query("neili", me) < 800 )
                return notify_fail("��������������ߣ�\n");

        if( (int)me->query_skill("cuff") < 220 )
                return notify_fail("���ȭ���������ң��޷���������ȭ�ĸ����ܾ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 220)
                return notify_fail("������ȭ����Ϊ���������ܹ��������! \n");

        if( (int)me->query_skill("force", 1) < 220)
                return notify_fail(HIM "��Ļ����ڹ���Ϊ���㣬�������ʹ�ò����! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("��û�м�������ȭ���޷����ò������\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ�����������\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�ô��У�\n");


        msg = HIY "$N��������ʹ������ȭ�ܾ��еġ�" HIR "�����" HIY "����˫ȭ������������$n��ȥ��\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -200, me);

                msg = HIG "$n��$Nȭ��ɨ�У�ֻ��ȫ������ʧȴ��Ԧ�����⼱к��\n"NOR;
                neili_wound = damage_power(me, "cuff");
                neili_wound += query("jiali", me);
                if( neili_wound > query("neili", target) )
                        neili_wound = query("neili", target);
                if( query("neili", target) < 0 )
                        neili_wound = 0;
                addn("neili", -neili_wound, target);
                target->receive_wound("qi", neili_wound, me);
                if( !target->is_busy() )
                        target->start_busy(2);
                me->start_busy(2);
                str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                msg += "($n"+str+")\n";
        }
        else
        {
                msg = HIG "ֻ��$n���Ų�æ������һ���������$N�ı�ɱһ����\n"NOR;

                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}