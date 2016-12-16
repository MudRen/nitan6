#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用中华傲决来提升自己的防御力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if( query_temp("shield", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "双手平举过顶，运起中华傲决，全身顿时笼罩在劲气之中！\n" NOR, me);

        addn_temp("apply/armor", skill*2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill * 2 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -amount, me);
                delete_temp("shield", me);
                tell_object(me, "你的中华傲决运行完"
                            "毕，将内力收回丹田。\n");
        }
}
