#include <ansi.h>

inherit TESSERA;

mapping gems = ([
        "ruby":         "�챦ʯ",
        "topaz":        "�Ʊ�ʯ",
        "sapphire":     "����ʯ",
        "emerald":      "�����",
        "amethyst":     "��ˮ��",
        "diamond":      "ˮ����",
        "skull":        "����ͷ",
]);
mapping gems_color = ([
        "ruby":         HIR,
        "topaz":        HIY,
        "sapphire":     HIB,
        "emerald":      HIG,
        "amethyst":     MAG,
        "diamond":      HIW,
        "skull":        WHT,
]);

string *gems_level = ({
        "ϸ���",
        "",
        "ϡ��",
        "��֮",
});

string *gems_level_id = ({
        "chipped",
        "",
        "flawless",
        "magic",
});

string query_gem_name(string socket, int level) 
{
        return sprintf("%s%s%s"NOR, gems_color[socket], gems_level[level - 1], gems[socket]); 
}

string query_gem_id(string socket, int level) 
{
        if( gems_level_id[level - 1] == "" ) return socket; 
        return sprintf("%s %s", gems_level_id[level - 1], socket); 
}

void create()
{
        int level, i;
        string gem, s;

        i = random(15);
        if (i < 3) gem = "ruby";
        else if (i < 6) gem = "topaz";
        else if (i < 9) gem = "sapphire";
        else if (i < 12) gem = "emerald";
        //else if (i < 15) gem = "amethyst";
        //else if (i < 16) gem = "diamond";
        //else gem = "skull";
        else gem = "diamond";

        i = random(100);
        if (i < 50) { level = 1; s = "c"; }
        else if (i < 75) { level = 2; s = ""; }
        else if (i < 95) { level = 3; s = "f"; }
        else { level = 4; s = "m"; }
        
        set_name(query_gem_name(gem, level), ({query_gem_id(gem, level)}));
        set_weight(20);
        set("long", WHT "����һ�ű�ʯ�������ƺ�����ĳ�������ħ����\n" NOR);
        set("unit", "��");     
        set("no_beg", 1);
        set("no_steal", 1);
        set("no_pawn", 1);
        set("value", 100000 * level * level * level);
        set("material", s+gem);
        set("level", level);
        set("no_identify", 1);
        set("auto_load", 1);
        set("set_data", 1);
        setup();
}

