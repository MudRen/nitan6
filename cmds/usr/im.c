// im.c

#include <ansi.h>

#define IM_D "/adm/daemons/imd.c"

inherit F_CLEAN_UP;

int who_list(object me);
int register(object me,string pro);
void register_step1(string arg,object me,string pro);
void register_step2(string arg,object me,string pro,string account);
int help(object me);

int main(object me, string arg)
{
        string who, msg;
        if(!arg) return help(me);
        if(arg == "login") 
        {
                if( query_temp("im_fd", me) 
                && IM_D->query_users()[query_temp("im_fd", me)]["obj"] == me)   
                {
                        tell( me, "\n[IM Message]:你正在登入中，请用 im quit 离线。\n");
                        return 1;
                }

                tell( me, "\n[IM Message]:开始登入即时通讯精灵。\n");
                IM_D->login_irc(me);
                return 1;
        }

        if(!undefinedp(query_temp("im_fd", me))) 
        {
                if(arg == "who")
                { 
                        who_list(me);
                        return 1;
                }
                
                if(arg == "quit") 
                {
                        IM_D->send_command(query_temp("im_fd", me),"QUIT\r\n");
                        delete_temp("im_fd", me);
                        tell( me, "\n[IM Message]:即时通讯精灵离线了。\n");
                        return 1;
                }

                if(sscanf(arg,"tell %s %s",who,msg) == 2)
                        return IM_D->process_send_msg(me,who,msg);

                if(arg == "register msn") 
                {       
                        register(me,"MSN");
                        return 1;
                }
                
                if(arg == "register yahoo") 
                {
                        register(me,"YAHOO");
                        return 1;
                }
                
                if(sscanf(arg,"add %s %s",who,msg) == 2)
                {
                        if(who != "msn" && who != "yahoo")
                        {
                                tell( me, "\n[IM Message]:目前只能加入 msn 或是 yahoo 的好友名单。\n");
                                return 1;
                        }
                        IM_D->send_command(query_temp("im_fd", me), "PRIVMSG #bitlbee :add "+who+" "+msg);

                        tell( me, "\n[IM Message]:你把 "+msg +" 加入你的 "+who +" 好友名单。\n");
                        return 1;
                }

                if(sscanf(arg,"remove %s",who) == 1)
                {
                        int fd = query_temp("im_fd", me);

                        if(!undefinedp(IM_D->query_users()[fd]["list"]) 
                        && !undefinedp(IM_D->query_users()[fd]["list"][who]))
                        {
                                IM_D->send_command(fd,  "PRIVMSG #bitlbee :remove "+who);
                                tell( me, "\n[IM Message]:你把 "+who +" 从你的好友名单删除。\n");
                                return 1;
                        }

                        tell( me, "\n[IM Message]:没有这个人哦！\n");
                        return 1;
                }

                if(arg == "yes") 
                {
                        IM_D->send_command(query_temp("im_fd", me), "PRIVMSG #bitlbee : yes");
                        tell( me, "\n[IM Message]:你同意他把你加入他的好友名单。\n");
                        return 1;
                }

                if(arg == "no")
                {
                        IM_D->send_command(query_temp("im_fd", me),  "PRIVMSG #bitlbee : no");
                        tell( me, "\n[IM Message]:你不同意他加你进入他的好友名单。\n");
                        return 1;
                }

                if(sscanf(arg,"nick %s",msg))
                {
                        tell( me, "\n[IM Message]:你将名字改为："+msg+"。\n");
                        IM_D->send_command(query_temp("im_fd", me),  "PRIVMSG #bitlbee :nick msn \""+msg+"\"");
                        return 1;
                }
                tell( me,"\n[IM Message]:没有这项功能哦。\n");
        }
        else 
                tell( me,"你并没有登入\n");
        return 1;
}

void who_list(object me)
{
        mapping map = IM_D->query_users();
        tell( me,"好友名单列表：\n");

        foreach(int fd,mapping m in map)
        {
                if(m["obj"] == me && me->query_id(1) == m["id"] )
                {
                        foreach(string k,string* v in m["list"])
                        {
                                if(v[2] == m["id"] || v[2] == "root") continue;

                        tell( me, sprintf("(%-4s)[%-10s] %-70s \n",v[3]=="G"?"离开":"线上",v[2],v[4]+"("+v[0]+"@"+v[1]+")"));
                        }
                }
        }
        return;
}

void register(object me,string pro)
{
        tell( me,"[IM Message] 请输入你的 "+pro+" 帐号，或是按 . 取消:");
        input_to("register_step1",me, pro);
        return;
}

void register_step1(string arg,object me,string pro)
{
        if(arg[0] == '.') 
        {
                tell( me, "[IM Message] 取消设定。\n");
                return;
        }

        if(strlen(arg) < 5) 
        {
                tell( me, "[IM Message] 请输入你的 "+pro+" 帐号，或是按 . 取消:");
                input_to("register_step1",me,pro);
        }

        tell( me, "[IM Message] 请输入你的 "+pro+" 密码，或是按 . 取消:");
        input_to("register_step2",me,pro,arg);
}

void register_step2(string arg,object me,string pro,string account)
{
        if(arg[0] == '.') 
        {
                tell( me, "[IM Message] 取消设定。\n");
                return;
        }


        if(strlen(arg) < 5) 
        {
                tell( me, "[IM Message] 请输入你的 "+pro+" 密码，或是按 . 取消:");
                input_to("register_step2",me,pro,account);
        }

        IM_D->del_account( query_temp("im_fd", me), pro);
        IM_D->register_account( query_temp("im_fd", me),pro,account,arg);
        tell( me, "[IM Message] "+pro+" 帐号新增或修改完毕。\n");
}

int help(object me)
{
        write(@HELP
指令格式 : im [各项参数]
            
    这个指令可以让你登入网路上流行的即时通讯软体。目前支援的         
即时通讯软体有 MSN 、 YAHOO 这二项。

    不管你是第几次使用，要使用 im 时，必需先打 im login 作
登入的动作。

    因为网路传输的关系，有些讯息可能会延迟一些时间才会收到。
     
     im login           - 登入 im 系统。
     im quit            - 登出 im 系统。
     im who             - 列出你的好友名单。
     im register msn    - 注册 msn 帐号。
     im register yahoo  - 注册 yahoo 帐号。
     im add <protocol> <account> - 新增好友。
     im remove <account>- 移除好友。
     im no              - 不同意他人把你加入好友名单。
     im yes             - 同意他人把你加入好友名单。
     im nick <nick>     - 修改 msn 的昵称。
     im tell <id> <msg> - 传讯给某人。
HELP
        );
        return 1;
}