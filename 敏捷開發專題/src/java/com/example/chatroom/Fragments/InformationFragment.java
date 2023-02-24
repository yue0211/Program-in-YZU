package com.example.chatroom.Fragments;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;

import android.util.Log;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;

import com.example.chatroom.CalendarActivity;
import com.example.chatroom.people_searchActivity;
import com.example.chatroom.MainActivity2;
import com.example.chatroom.NextCalendarActivity;
import com.example.chatroom.ProfileActivity;
import com.example.chatroom.R;
import com.example.chatroom.price_searchActivity;

import java.time.OffsetDateTime;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;


public class InformationFragment extends Fragment {
    Button  comic_all, comic_nekketsu, comic_renai, comic_gakuen,
            comic_yuri, comic_bl, comic_bouken, comic_haaremu,
            comic_sf, comic_sensou, comic_suspense, comic_suiri,
            comic_haha, comic_miracle, comic_mahou, comic_kyoufu,
            comic_kishin, comic_rekishi, comic_doujin, comic_undou,
            comic_shinshi, comic_kikou, comic_H, comic_other;

    Button game_submit;

    Button top, food_panda, surugaya, toranoana, booth, animate, yuyutei;

    RadioButton people_search;
    RadioButton price_search;

    RadioButton this_season;
    RadioButton next_season;

    RadioButton detail;
    RadioButton calendar;

    String TAG = InformationFragment.class.getSimpleName();


    public Pair<String, String> getSeason(int timeZone){
        Pair<String, String> time = getTime(timeZone);
        String year = time.first, month = time.second, seasonMonth = "", nextSeasonMonth = "";

        switch (month)
        {
            case "01":
            case "02":
            case "03":
                seasonMonth = "01";
                nextSeasonMonth = "04";
                break;
            case "04":
            case "05":
            case "06":
                seasonMonth = "04";
                nextSeasonMonth = "07";
                break;
            case "07":
            case "08":
            case "09":
                seasonMonth = "07";
                nextSeasonMonth = "10";
                break;
            case "10":
            case "11":
            case "12":
                seasonMonth = "10";
                nextSeasonMonth = "01";
                break;
        }

        Pair<String, String> tpair = new Pair<>(year+seasonMonth, year+nextSeasonMonth);

        return tpair;
    }


    public Pair<String, String> getTime(int timeZone){
        DateTimeFormatter t1 = DateTimeFormatter.ofPattern("uuuu");
        DateTimeFormatter t2 = DateTimeFormatter.ofPattern("MM");

        ZoneOffset offset = ZoneOffset.ofHours( timeZone );
        OffsetDateTime odt = OffsetDateTime.now( offset );
        String t1s = odt.format( t1 ), t2s = odt.format( t2 );

        Pair<String, String> tpair = new Pair<>(t1s, t2s);
        return tpair;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_information, container, false);

        top = view.findViewById(R.id.Anime_submit);

        people_search = view.findViewById(R.id.people_search);
        price_search  =  view.findViewById(R.id.price_search);

        this_season = view.findViewById(R.id.this_season);
        next_season = view.findViewById(R.id.next_season);

        detail = view.findViewById(R.id.detail);
        calendar = view.findViewById(R.id.calendar);

        game_submit = view.findViewById(R.id.game_submit);

        top.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Pair<String, String> seasonTimes = getSeason(8);
                String seasonTime = seasonTimes.first, nextSeasonTime = seasonTimes.second;
                String url = "https://acgsecrets.hk/bangumi/";

                Intent intent = new Intent(Intent.ACTION_VIEW);

                if(this_season.isChecked() && detail.isChecked())
                {
                    intent.setData(Uri.parse(url+seasonTime));
                    startActivity(intent);
                }
                else if(next_season.isChecked() && detail.isChecked())
                {
                    intent.setData(Uri.parse(url+nextSeasonTime));
                    startActivity(intent);
                }

                if(calendar.isChecked())
                {
                    if(this_season.isChecked())
                    {
                        Intent Calendar = new Intent(getActivity(), CalendarActivity.class);
                        startActivity(Calendar);
                    }
                    else if(next_season.isChecked())
                    {
                        Intent NextCalendar = new Intent(getActivity(), NextCalendarActivity.class);
                        startActivity(NextCalendar);
                    }
                }
            }
        });


        game_submit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(people_search.isChecked())
                {
                    Intent people_search = new Intent(getActivity(), people_searchActivity.class);
                    startActivity(people_search);
                }

                if(price_search.isChecked())
                {
                    Intent price_search = new Intent(getActivity(), price_searchActivity.class);
                    startActivity(price_search);
                }


            }
        });





        comic_all = view.findViewById(R.id.comic_all);
        comic_all.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=all&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_nekketsu = view.findViewById(R.id.comic_nekketsu);
        comic_nekketsu.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=1&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_renai = view.findViewById(R.id.comic_renai);
        comic_renai.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=2&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_gakuen = view.findViewById(R.id.comic_gakuen);
        comic_gakuen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=3&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_yuri = view.findViewById(R.id.comic_yuri);
        comic_yuri.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=4&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_bl = view.findViewById(R.id.comic_bl);
        comic_bl.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=5&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_bouken = view.findViewById(R.id.comic_bouken);
        comic_bouken.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=6&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_haaremu = view.findViewById(R.id.comic_haaremu);
        comic_haaremu.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=7&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_sf = view.findViewById(R.id.comic_sf);
        comic_sf.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=8&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_sensou = view.findViewById(R.id.comic_sensou);
        comic_sensou.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=9&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_suspense = view.findViewById(R.id.comic_suspense);
        comic_suspense.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=10&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_suiri = view.findViewById(R.id.comic_suiri);
        comic_suiri.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=11&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_haha = view.findViewById(R.id.comic_haha);
        comic_haha.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=12&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_miracle = view.findViewById(R.id.comic_miracle);
        comic_miracle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=13&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_mahou = view.findViewById(R.id.comic_mahou);
        comic_mahou.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=14&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_kyoufu = view.findViewById(R.id.comic_kyoufu);
        comic_kyoufu.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=15&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_kishin = view.findViewById(R.id.comic_kishin);
        comic_kishin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=16&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_rekishi = view.findViewById(R.id.comic_rekishi);
        comic_rekishi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=17&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_doujin = view.findViewById(R.id.comic_doujin);
        comic_doujin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=18&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_undou = view.findViewById(R.id.comic_undou);
        comic_undou.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=19&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_shinshi = view.findViewById(R.id.comic_shinshi);
        comic_shinshi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=20&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_kikou = view.findViewById(R.id.comic_kikou);
        comic_kikou.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=21&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_H = view.findViewById(R.id.comic_H);
        comic_H.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=22&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });

        comic_other = view.findViewById(R.id.comic_other);
        comic_other.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://mh5.tw/allcartoonlist?page=1&order=0&sort_type=2&class_id=23&ut_id=&area_id=3&status=all"));
                startActivity(intent);
            }
        });



        food_panda = view.findViewById(R.id.food_panda);
        food_panda.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://www.foodpanda.com.tw/?gclid=Cj0KCQjwma6TBhDIARIsAOKuANyM79m6f1DsDLlOHQteI67gFVfEpz4gm8GJ1X7uQGPsjQbgIT3gcAIaAl2SEALw_wcB"));
                startActivity(intent);
            }
        });

        surugaya = view.findViewById(R.id.surugaya);
        surugaya.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://www.suruga-ya.jp/?utm_campaign=JUNHKDP&utm_medium=bitly&utm_source=blogpost"));
                startActivity(intent);
            }
        });

        toranoana = view.findViewById(R.id.toranoana);
        toranoana.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://ec.toranoana.jp/"));
                startActivity(intent);
            }
        });

        booth = view.findViewById(R.id.booth);
        booth.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://booth.pm/ja"));
                startActivity(intent);
            }
        });

        animate = view.findViewById(R.id.animate);
        animate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://www.animate-onlineshop.jp/?utm_campaign=JUNHKDP&utm_medium=bitly&utm_source=blogpost"));
                startActivity(intent);
            }
        });

        yuyutei = view.findViewById(R.id.yuyutei);
        yuyutei.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("https://yuyu-tei.jp/"));
                startActivity(intent);
            }
        });











        return view;
    }

}