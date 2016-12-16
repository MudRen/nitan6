#include <ansi.h>
#include <combat.h>

#define QIAN "��" HIW "ǧ���ݺ���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if( userp(me) && !query("can_perform/wushen-jian/qian", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" QIAN "��\n");

        if ((int)me->query_skill("wushen-jian", 1) < 200)
                return notify_fail("��ĺ�ɽ���񽣲�����죬����ʩչ" QIAN "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������ʩչ" QIAN "��\n");

        if (me->query_skill_mapped("sword") != "wushen-jian")
                return notify_fail("��û�м�����ɽ���񽣣�����ʩչ" QIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "��ת��ɽ���񽣣�����" + weapon->name() +
              HIW "�ų��������⣬�����ɺ����죬ϯ��$n" HIW "��ȥ��" NOR;

        message_sort(msg, me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        attack_time = 4;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "���$n" HIR "��$N" HIR "���˸����ֲ�����$n"
                      HIR "��æ�мܣ����нпࡣ\n" NOR;

                count = ap / 20;
                attack_time += random(ap / 45);
        } else
        {
                msg = HIC "$n" HIC "��$N" HIC "�⼸����ʽ������������"
                      "����ֻ�ÿ���мܡ�\n" NOR;
                count = 0;
        }
            message_combatd(msg, me, target);

        if (attack_time > 9)
                attack_time = 9;

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count/2, me);
        addn("neili", -attack_time*30, me);
        me->start_busy(1 + random(attack_time / 2));

        set_temp("perform_wushenjian/qian", 1, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                       break;

                if (! target->is_busy() && random(3) == 1)
                       target->start_busy(1);
 
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        delete_temp("perform_wushenjian/qian", me);

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count/2, me);
        return 1;
}