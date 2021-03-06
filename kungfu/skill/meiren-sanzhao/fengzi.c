// fengzi.c

#include <ansi.h>
inherit F_SSERVER;

string name() { return "绝世风姿"; }

int perform(object me, object target)
{
        int level;
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() ||
                  !me->is_fighting(target) ||
          !living(target) || query_temp("no_living", target) )
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( (query("gender", me) != "女性" || me->query_per()<20) && !wizardp(me) )
                return notify_fail("象你这副尊容，恐怕再怎么样，也没人多看你一眼的。\n");

        if( query("gender", target) != "男性" )
                return notify_fail("怎么了？卖弄风骚也要找个正确对象吧？\n");

        if( level = me->query_skill("meiren-shanzhao", 1) < 150 )
                return notify_fail("你的美人三招不够娴熟，不会使用"+name()+"。\n");

        if( (int)me->query_skill("force", 1) < 160 )
                return notify_fail("你的内功不够娴熟，不会使用"+name()+"。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的内力不足，恐怕没法摆什么风姿了。\n");

        if( query_temp("shenlong/fengzi", target) )
                return notify_fail("他已经对你很倾倒了，你还浪费什么表情？\n");

        addn("neili", -200, me);
        me->start_busy(1);
        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                message_combatd(HIC"激斗中，却见$N"HIC"忙中不乱，冲着$n"HIC"轻轻展颜露齿一笑，端的是艳若桃李、灿若明霞，容色柔媚无限，\n"
                        "$n心中不觉一荡，油然升起一股亲近的感觉，眼神也渐渐迷茫起来。\n" NOR, me, target);
                set_temp("shenlong/fengzi", 1, target);
                addn_temp("apply/defense", -level, target);
                if( !target->is_busy() )
                        target->start_busy(random(3)+1);
                target->start_call_out( (: call_other, __FILE__, "remove_effect", target, level:), 30);
        }
        else
        {
                message_combatd(HIY"只见$N"HIY"冲着$n"HIY"轻轻露齿一笑，露出了牙缝中一丝没咽下去的"HIG"菜叶"HIY"。\n" NOR, me, target);
        }
        return 1;
}
void remove_effect(object target, int level)
{
        delete_temp("shenlong/fengzi", target);
        addn_temp("apply/defense", level, target);
        message_combatd(HIG"$N迷茫的眼神忽然一亮，心头猛地一震，忙收拢起心神来。\n" NOR, target);
}

