#include <ansi.h>
#include <combat.h>

string name() { return HIR "���Ӹ���" NOR; }

#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            (query("id", weapon) != "qizi gangbiao" &&
             query("skill_type", weapon) != "throwing") )
                return notify_fail("����������û�����Ű������Ӹ��ڣ�����ʩչ" + name() + "��\n");

        if( query("id", weapon) != "qizi gangbiao" &&
             weapon->query_amount() < 7)
                return notify_fail("����������û���㹻�İ���������ʩչ" + name() + "��\n");

        if ((skill = me->query_skill("tangmen-throwing", 1)) < 120)
                return notify_fail("������Ű���������죬����ʩչ" + name() + "��\n");

        if( query("tangmen/yanli", me)<80 )
                return notify_fail("�������̫���ˣ�Ŀ�겻��ȷ���޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("boyun-suowu", 1) < 120)
                return notify_fail("��Ĳ�������������죬�޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -100, me);

        msg = HIR "\n$N" HIR "ͻȻ����һֹ���ӻ���������ö���ƴ�С��" + weapon->name() + HIR "��һ������$n " HIR "��ȥ��\n"
              "ֻ����ö" + weapon->name() + HIR "�����������$n" HIR "�����������������Ĺ�Ӱ��ȴ������һ˿������\n"NOR;

        ap = attack_power(me, "throwing");
        dp = defense_power(target, "parry") +
             target->query_skill("dugu-jiujian", 1);

        message_combatd(msg, me, target);
        tell_object(target, HIR "\n�㼱æ��������ϣ���ܹ��м���������һ����\n"NOR);
        if (ap / 2 + random(ap) > dp)
        {
                if( query("id", weapon) != "qizi gangbiao" )
                {
                        n = 7;
                        weapon->add_amount(-7);
                        damage = damage_power(me, "throwing");
                        damage+= query("jiali", me);
                        msg = HIR "���$p" HIR "һ���Һ���������$P" HIR "��������" +
                                query("base_unit", weapon)+weapon->name()+HIR"��\n"NOR;

                        while (n--)
                        {
                                COMBAT_D->clear_ahinfo();
                                weapon->hit_ob(me, target,
                                               query("jiali", me)+100+n*10);
                        }

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage, me);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);
                        me->start_busy(2);
                        return 1;
                }
                msg = HIR "��Ȼ�������Ĺ�Ӱһ����û��$n����һ�٣����һ����Ѫ�����������\n" NOR;
                message_combatd(msg, me, target);
                tell_object(target, HIR "��ֻ�����ؿ�һ�����ĵ���ʹ����ͷһ��ֻ������ö�����Ѿ������Ƕ������Ŀڡ�\n"
                                    "Ѫ������Լ�м���С��[���Ӹ���...]��\n"NOR);
                weapon->hit_ob(me,target,query("jiali", me)+200);
                weapon->move(target);


                target->receive_wound("qi", 100, me);
                COMBAT_D->clear_ahinfo();
                target->unconcious(me);
                me->start_busy(2);
        } else
        {
                tell_object(target, HIR "��Ȼ�������Ĺ�Ӱһ����û��������һ����æ��������ȫ����\n" NOR);
                msg = HIR "$n" HIR "˫�ۼ��裬��������Ʒ�֮����ֻ������һ�����죬��������ö�����ķɿ�ȥ��\n" NOR;
                message_combatd(msg, me, target);
                if( query("neili", target)<1000 )
                        set("neili", 0, target);
                else
                        addn("neili", -1000, target);
                weapon->move(environment(me));
                me->start_busy(3);
        }
        return 1;
}
