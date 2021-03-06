#include <ansi.h>

inherit F_SSERVER;

string name() { return HIY "飞天神行" NOR; }


void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count, cnt, skill;

        if( query_temp("fei_tian", me) )
                return notify_fail("你已经运起" + name() + "了。\n");

        if ((int)me->query_skill("sixiang-bufa", 1) < 150)
                return notify_fail("你的四象步法等级不够，难以施展" + name() + "。\n");

        if ((int)me->query_dex() < 33)
                return notify_fail("你的身法不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("dodge", 1) < 150)
                return notify_fail("你的轻功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你此时的内力不足，难以施展" + name() + "。\n");

        msg = HIY "$N" HIY "足尖轻点地面，凌空跃起，身形顿时变得飘忽不定，难以捉摸。\n\n" NOR;

        message_combatd(msg, me, target);
        skill = me->query_skill("sixiang-bufa", 1);
        cnt = (int)((int)me->query_condition("drunk") / 3);

        count = skill / 20;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("dex", count, me);
        set_temp("fei_tian", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("fei_tian", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("fei_tian", me);
                tell_object(me, "你的" + name() + "运行完毕，将内力收回丹田。\n");
        }
}
