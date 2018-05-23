// zhizhu_poison.c
#include <ansi.h>

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( query_temp("nopoison", me))return 0;
        if( duration < 1 ) return 0;

        me->receive_wound("qi", 15+random(10), "蜘蛛毒发作");
        me->receive_damage("jing", 15+random(10), "蜘蛛毒发作");
        tell_object(me, HIG"你发现伤口一丝丝的黑线正在扩张中。你中的蜘蛛毒发作了！\n" NOR );
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("zhizhu_poison", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "poison";
}