// This is player's own perform (Write by Lonely@nt2)
//CreatebyС��(Xiaodao)atTue Aug 19 17:52:34 2014
// ���־�(lian)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "���־�" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (member_array("cuff", weapon_sk) != -1)
        {
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "cuff" )
                        return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");
        } else
        {
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n");
        }

        if ((int)me->query_skill("taiji-quan", 1) < 400)
                return notify_fail("��" + to_chinese("taiji-quan") + "������죬����ʩչ" + name() + "��\n");

        if (member_array("cuff", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("cuff") != "taiji-quan")
                        return notify_fail("��û��׼��" + to_chinese("taiji-quan") + "������ʩչ" + name() + "��\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$Nһ��ŭ������̫�������˼�����˫ȭ��ʱЯ���������֮�ƽӶ������ù���$n����" + "\n" + NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        attack_time = 6;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIM "���$n���ܲ�����$N��ȭ���ƾ���ʱ͸����룬������Ѫ���磬����������" + "\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
        } else
        {
                msg += NOR + CYN "����$pʶ����$P��һ�У�ббһԾ�ܿ���" + "\n" NOR;
                count = 0;
        }

        message_sort(msg, me, target);

        attack_time+=query("jieti/times", me)*2;
        if (attack_time > 13)
                attack_time = 13;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy()) target->start_busy(1);

                COMBAT_D->do_attack(me, target, (member_array("cuff", weapon_sk) == -1 ? 0 : weapon), 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(3 + random(attack_time/ 3));

        return 1;
}