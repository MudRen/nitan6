// vote unjail
#include <command.h> 
#include <vote.h> 
#include <ansi.h>
#define JAIL "/d/beijing/jail"

inherit F_CONDITION;

int clear_vote(object me);

int vote(object me, object victim)
{
  int reason; // vote for what?
  int vv;        // valid voter numbers
  int vc;         // vote count;
  int df;
  int i;
  string *juror, my_ip , *ips;
  object *inv;

  if (base_name(environment(victim))!= JAIL)
  {
         return notify_fail("你投票的人不在刑部大牢!\n");
  }

  if (me == victim)
  {
        if (random(2)) addn("vote/abuse", 10, me);
          return notify_fail("你不是开玩笑吧？当心被剥夺表决权！\n");
  }

  if( (reason=query("vote/reason", victim))>0 && (reason != V_CHBLK) )
  {
          return notify_fail("要把当前的表决完成以后才可以提新的动议。\n");
  }

  if (reason <= 0)
  {
          set("vote/reason", V_CHBLK, victim);
  }
  
  my_ip = query_ip_name(me);

  // dont allow me to vote twice for the same issue
  juror=query("vote/juror", victim);
  
  if( !pointerp(juror) )
  {
         set("vote/juror", ({my_ip}), victim);
  } else if( member_array(my_ip, juror) == -1 || wizardp(me)) 
  {
         set("vote/juror", juror+({my_ip}), victim);
  } else
  {
        addn("vote/abuse", 10, me);
          return notify_fail("一人一票！滥用表决权是要受惩罚的！\n");
  }

/*  vv = (int) ("/cmds/std/vote")->valid_voters(me)/2;  
  addn("vote/count", 1, vc=victim);

  df = (int)((vv - vc)/2);
  if (vv < 4) df = 4 - vc;*/
  ips = ("/cmds/std/vote")->valid_voters(me);
  vv = sizeof(ips);
  for (i=0;i<sizeof(juror);i++)
  {
          if (member_array(juror[i],ips)==-1)
           addn("vote/count", -1, vc=victim);
  }
  addn("vote/count", 1, vc=victim);

  df = vv - vv/2 - vc;
  if (vv < 8) df = 4 - vc;

  if (df>0)
  {
        shout( HIG "【表决】"+me->name()+"投票将" +victim->name()
                        +"放出刑部大牢，还差"+sprintf("%d", df)+"票。\n" NOR);
        write( HIG "【表决】"+me->name()+"投票将" +victim->name()
                        +"放出刑部大牢，还差"+sprintf("%d", df)+"票。\n" NOR);
        victim->apply_condition("vote_clear", 10);
  } else 
  {
        shout( HIG "【表决】"+me->name()+"投票将" +victim->name()
                        +"放出刑部大牢。"+victim->name()+"已经被放出刑部大牢了！\n" NOR);
        write( HIG "【表决】"+me->name()+"投票将" +victim->name()
                        +"放出刑部大牢。"+victim->name()+"已经被放出刑部大牢了！\n" NOR);
                        
        victim->apply_condition("vote_clear", -10);
        if( !wizardp(victim) ) {
                inv = all_inventory(victim);
                for(i=0; i<sizeof(inv); i++)
                        if( !inv[i]->query_autoload() )
                                DROP_CMD->do_drop(victim, inv[i]);
        }
        delete("vote/juror", victim);
        delete("xkx_jail", victim);
        victim->move("/d/city/wumiao");
  } 
  
  return 1;
}
