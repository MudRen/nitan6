// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用怒海狂涛提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够!");

        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "纵声长笑，丹田中内力激荡，"
                        "衣角猛然扬起，内力似乎向洪水般向外涌出！\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/unarmed_damage", skill*2/5, me);
        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill * 2 / 5 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/unarmed_damage", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的怒海狂涛运行完毕，将内力收回丹田。\n");
        }
}
