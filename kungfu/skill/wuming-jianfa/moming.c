// 剑动莫名

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "剑动莫名"; }
int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i,j,times,n;

        i = me->query_skill("wuming-jianfa", 1)/60;
        j = me->query_skill("sword")/60;

        if (! target) 
        {
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }
        if (! target || ! me->is_fighting(target)) 
                return notify_fail("你只能对战斗中的对手使用绝招「剑动莫名」。\n"); 
        if( !objectp(weapon=query_temp("weapon", me)))return notify_fail("你必须使用武器才能使用「剑动莫名」！\n");
        //if ( base_name(weapon)!="/clone/weapon/yuenv" ) return notify_fail("你必须手持越女朝阳剑才能使用「剑动莫名」！\n");
        if ( (int)me->query_str() < 35 ) return notify_fail("你的臂力不够, 还不能使用这项绝技! \n");
        if ( (int)me->query_skill("sword",1) < 600 ) return notify_fail("你的基本剑法的火候还不到家, 不能使用这一绝技 !\n");
        if ( (int)me->query_skill("wuming-jianfa", 1) < 500 ) return notify_fail("你的无名剑法的火候还不到家, 不能使用这一绝技 !\n");
        if( query("neili", me)<50000)return notify_fail("你的真气不够！\n");
        if( query("max_neili", me)<50000)return notify_fail("你的内力修为不够！\n");
        if ( me->is_busy() ) return notify_fail("你上一个动作还没有完成！\n");

        msg = MAG "\n$N脸现幽思,往事如潮涌上心头,手中剑望空斜指一股怨气从剑尖散发弥漫开来！\n" NOR;
        message_combatd(msg, me);
        ob = target;
        addn_temp("apply/str", i, me);
        addn_temp("apply/attack", j, me);
        times = (int)(me->query_skill("wuming-jianfa", 1)/50) - 1;
        if( times > 12 ) times = 12;
        for ( n=0; n<times; n++ )
        {
                if ( !ob ) break;
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me),1);
        }
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -j, me);
        addn("neili", -random(5000)-5000, me);
        me->start_busy(random(2)+2);
        if ( ob && !ob->is_busy() ) ob->start_busy(random(2)+1);
        return 1;
}
