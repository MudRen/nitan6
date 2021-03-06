// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用辟邪剑法提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够！\n");

        if (me->query_skill("pixie-jian", 1) < 120)
                return notify_fail("你的辟邪剑法修行不够，难以运功。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "身形忽然变得诡秘异常，进退"
                        "之间飘忽不定，令人无从捉摸。\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill*2/5, me);
        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int level)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -(level/3), me);
                addn_temp("apply/defense", -(level*2/5), me);
                delete_temp("powerup", me);
                tell_object(me, "你的辟邪剑法运行完毕，将内力收回丹田。\n");
        }
}
