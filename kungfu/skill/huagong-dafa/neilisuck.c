// Code of ShenZhou
// neilisuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp;
        int dmg;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("你要吸取谁的内力？\n");

       if( query("no_fight", environment(me)) )
              return notify_fail("这里不能战斗，你不可以使用化功大法吸人的内力。\n");

        if( query_temp("sucked", me) )
                return notify_fail("你刚刚吸取过内力！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能施用化功大法吸人内力！\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("你必须在战斗中才能吸取对方的内力！\n");

        if( (int)me->query_skill("huagong-dafa",1) < 60 )
                return notify_fail("你的化功大法功力不够，不能吸取对方的内力！\n");

        if( query("neili", me)<50 )
                return notify_fail("你的内力不够，不能使用化功大法。\n");

        if( query("jingli", me)<20 )
                return notify_fail("你的精力不够，不能使用化功大法。\n");

        if( query("neili", me) >= query("max_neili", me)*2 )
                return notify_fail("你吸取的内力充塞全身，无法再吸取内力！\n");

        if( query("max_neili", target) <= 1 )
                return notify_fail( target->name() +
                        "没有任何内力！\n");

        if( query("neili", target)<query("max_neili", target)/10 )
                return notify_fail( target->name() +
                        "已经内力涣散，你已经无法从他体内吸取任何内力了！\n");

        message_vision(
                HIW "$N一张脸突然变得惨白，右掌直出，猛地对准$n的膻中大穴按了上去！\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp=me->query_skill("force")+me->query_skill("dodge")+query("kar", me)*50;
        dp=target->query_skill("force")+target->query_skill("dodge")+query("kar", target)*50;
        sp+=query("combat_exp", me)/1000;
        dp+=query("combat_exp", target)/1000;

        set_temp("sucked", 1, me);

        if( random(sp+dp) > dp )
        {
                message_vision(
                        HIR "$N顿觉膻中微痛，如同被尖针刺了个小孔，全身内力如水银般循孔飞泄而出！\n\n" NOR,
                        target );

                tell_object(me, HIG "你觉得" + target->name() + "的内力自手掌源源不绝地流了进来。\n" NOR);

                if( query("neili", target)>me->query_skill("force") )
                {
                        addn("neili", -1*me->query_skill("force"), target);
                        addn("neili", 2*(me->query_skill("force")), me);
                }else{
                        addn("neili", 2*query("neili", target), me);
                        set("neili", 0, target);
                }

                if( query("combat_exp", target) >= query("combat_exp", me)/2){
                        addn("potential", 1, me);
                        addn("combat_exp", 1, me);
                        if( query("potential", me)>me->query_potential_limit() )
                    set("potential", me->query_potential_limit(), me);
                }

                me->start_busy(1+random(3));
                target->start_busy(1+random(3));
                addn("neili", -me->query_skill("force")/7, me);
                addn("jingli", -5, me);

                COMBAT_D->report_status(target);

                call_out("del_sucked", 1+random(2), me);
        }
        else
        {
                message_vision(HIY "可是$p看破了$P的企图，机灵地闪了开去。\n" NOR, me, target);
                addn("jingli", -10, me);
                me->start_busy(1 + random(3) );
                call_out("del_sucked", 2+random(3), me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}