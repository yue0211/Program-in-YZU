package com.example.chatroom;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.app.ActionBar;
import android.content.res.Resources;
import android.graphics.Color;
import android.opengl.Visibility;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Looper;
import android.os.SystemClock;
import android.text.Html;
import android.text.InputType;
import android.text.method.LinkMovementMethod;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Spinner;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.engine.Resource;
import com.example.chatroom.Model.User;
import com.google.android.material.tabs.TabLayout;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import de.hdodenhof.circleimageview.CircleImageView;
import android.os.AsyncTask;




public class people_searchActivity extends AppCompatActivity {

    CircleImageView profile_image;
    TextView username;

    FirebaseUser firebaseUser;
    DatabaseReference reference;

    private TableLayout tab,tab2;

    public ArrayList<HashMap<String, String>> contactList, nContactList;

    private String TAG = people_searchActivity.class.getSimpleName();

    private TextView reading;

    private boolean status;

    private static String url = "https://api.jsonstorage.net/v1/json/a3452525-1db6-4e5d-8fb2-bbc1ba227a54/7ade52c5-1777-4cf7-aee9-2768073be611";

    public ArrayList<HashMap<String, String>> week1,week2,week3,week4,week5,week6,week7;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_people_search);
        new people_searchActivity.GetContacts().execute();
        threadRun();

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setTitle("");


        contactList = new ArrayList<>();
        nContactList = new ArrayList<>();

        reading =  findViewById(R.id.reading);

        status = false;

        profile_image = findViewById(R.id.profile_image);
        username = findViewById(R.id.username);

        firebaseUser = FirebaseAuth.getInstance().getCurrentUser();
        reference = FirebaseDatabase.getInstance().getReference("Users").child(firebaseUser.getUid());

        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot)
            {
                User user = snapshot.getValue(User.class);
                username.setText(user.getUsername());

                if(user.getImageURL() != null)
                    if(user.getImageURL().equals("default"))
                        profile_image.setImageResource(R.mipmap.ic_launcher);
                    else
                        Glide.with(getApplicationContext()).load(user.getImageURL()).into(profile_image);

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        tab = findViewById(R.id.tabla_cuerpo);
        tab2 = findViewById(R.id.tabla_cuerpo2);

    }

    private void update(){

        for(int i = 0; i <contactList.size(); i++)
        {
            Log.e(TAG,contactList.get(i).get("update")+"測試"+i);

            TableRow tbrow0 = new TableRow(people_searchActivity.this);
            TableRow.LayoutParams lp = new TableRow.LayoutParams(TableRow.LayoutParams.WRAP_CONTENT,TableRow.LayoutParams.WRAP_CONTENT);
            tbrow0.setLayoutParams(lp);

            TableRow.LayoutParams params = new TableRow.LayoutParams(0, ActionBar.LayoutParams.MATCH_PARENT,1);

            TextView tv0 = new TextView(people_searchActivity.this);
            tv0.setLayoutParams(params);
            tv0.setGravity(Gravity.LEFT);
            tv0.setTextAppearance(android.R.style.TextAppearance_Medium);
            tv0.setBackgroundResource(R.drawable.cell_shape);

            tv0.setInputType(InputType.TYPE_CLASS_TEXT |
                    InputType.TYPE_TEXT_FLAG_MULTI_LINE |
                    InputType.TYPE_TEXT_FLAG_CAP_SENTENCES);
            tv0.setMaxWidth(R.dimen.my_dimen);
            tv0.setMaxLines(50);
            String URL = "<a href=\""+ contactList.get(i).get("url") + "\">" + contactList.get(i).get("Title") + "</a>";
            tv0.setText(Html.fromHtml(URL));
            tv0.setMovementMethod (LinkMovementMethod.getInstance());
            tbrow0.addView(tv0);


            TextView tv1 = new TextView(people_searchActivity.this);
            tv1.setLayoutParams(params);
            tv1.setText(contactList.get(i).get("price_new"));
            tv1.setTextAppearance(android.R.style.TextAppearance_Medium);
            tv1.setBackgroundResource(R.drawable.cell_shape);
            tv1.setGravity(Gravity.CENTER);


            tv1.setInputType(InputType.TYPE_CLASS_TEXT |
                    InputType.TYPE_TEXT_FLAG_MULTI_LINE |
                    InputType.TYPE_TEXT_FLAG_CAP_SENTENCES);
            tv1.setMaxWidth(R.dimen.my_dimen);
            tv1.setMaxLines(50);
            tbrow0.addView(tv1);

            String priceString = contactList.get(i).get("price_cut");
            float price = 100-Float.parseFloat(priceString);
            String coupon = "";

            if(price%10==0)
            {
                price/=10;

                switch((int) price)
                {
                    case 1:
                        coupon = "一折";
                        break;
                    case 2:
                        coupon = "二折";
                        break;
                    case 3:
                        coupon = "三折";
                        break;
                    case 4:
                        coupon = "四折";
                        break;
                    case 5:
                        coupon = "五折";
                        break;
                    case 6:
                        coupon = "六折";
                        break;
                    case 7:
                        coupon = "七折";
                        break;
                    case 8:
                        coupon = "八折";
                        break;
                    case 9:
                        coupon = "九折";
                        break;

                }
            }
            else{

                float ten = price/10;
                float box = price%10;

                switch((int) ten)
                {
                    case 1:
                        coupon += "一";
                        break;
                    case 2:
                        coupon += "二";
                        break;
                    case 3:
                        coupon += "三";
                        break;
                    case 4:
                        coupon += "四";
                        break;
                    case 5:
                        coupon += "五";
                        break;
                    case 6:
                        coupon += "六";
                        break;
                    case 7:
                        coupon += "七";
                        break;
                    case 8:
                        coupon += "八";
                        break;
                    case 9:
                        coupon += "九";
                        break;

                }

                switch((int) box)
                {
                    case 1:
                        coupon += "一折";
                        break;
                    case 2:
                        coupon += "二折";
                        break;
                    case 3:
                        coupon += "三折";
                        break;
                    case 4:
                        coupon += "四折";
                        break;
                    case 5:
                        coupon += "五折";
                        break;
                    case 6:
                        coupon += "六折";
                        break;
                    case 7:
                        coupon += "七折";
                        break;
                    case 8:
                        coupon += "八折";
                        break;
                    case 9:
                        coupon += "九折";
                        break;

                }

            }


            TextView tv2 = new TextView(people_searchActivity.this);
            tv2.setLayoutParams(params);
            tv2.setText(coupon);
            tv2.setTextAppearance(android.R.style.TextAppearance_Medium);
            tv2.setBackgroundResource(R.drawable.cell_shape);
            tv2.setGravity(Gravity.CENTER);


            tv2.setInputType(InputType.TYPE_CLASS_TEXT |
                    InputType.TYPE_TEXT_FLAG_MULTI_LINE |
                    InputType.TYPE_TEXT_FLAG_CAP_SENTENCES);
            tv2.setMaxWidth(R.dimen.my_dimen);
            tv2.setMaxLines(50);
            tbrow0.addView(tv2);

            tab.addView(tbrow0);
        }


    }


    private void threadRun() {
        new Thread(() -> {
            for (int i = 1; i < 5; i++)
            {
                runOnUiThread(() -> {
                    if(status)
                    {
                        reading.setVisibility(View.GONE);
                        update();
                        status = false;
                        Log.e(TAG,"跑啊 幹");
                    }
                });
                SystemClock.sleep(1000);
            }


        }).start();
    }




    public class GetContacts extends AsyncTask<Void, Void, Void> {


        @Override
        protected void onPreExecute() {
            super.onPreExecute();
        }

        @Override
        protected Void doInBackground(Void... arg0) {
            HttpHandler sh = new HttpHandler();



            // Making a request to url and getting response
            String jsonStr = sh.makeServiceCall(url);

            if (jsonStr != null)
            {
                try
                {
                    JSONObject jsonObj = new JSONObject(jsonStr);
                    JSONArray contacts = jsonObj.getJSONArray("Steam");
                    Log.e(TAG, "Steam " + contacts.length());

                    for (int i = 0; i < contacts.length(); i++)
                    {
                        JSONObject c = contacts.getJSONObject(i);

                        String name = c.getString("Title");
                        String first = c.getString("price_new");
                        String update = c.getString("price_cut");
                        String URL = c.getString("url");

                        HashMap<String, String> contact = new HashMap<>();

                        contact.put("Title", name);
                        contact.put("price_new", first);
                        contact.put("price_cut", update);
                        contact.put("url", URL);

                        contactList.add(contact);
                    }
                }
                catch(final JSONException e)
                {
                    Log.e(TAG, "Json parsing error: " + e.getMessage());
                    runOnUiThread(new Runnable()
                    {
                        @Override
                        public void run()
                        {
                            Toast.makeText(getApplicationContext(),
                                    "Json parsing error: " + e.getMessage(),
                                    Toast.LENGTH_LONG).show();
                        }
                    });
                }
            }
            else
            {
                Log.e(TAG, "Couldn't get json from server.");
                runOnUiThread(new Runnable()
                {
                    @Override
                    public void run()
                    {
                        Toast.makeText(getApplicationContext(),
                                "Couldn't get json from server. Check LogCat for possible errors!",
                                Toast.LENGTH_LONG)
                                .show();
                    }
                });
            }

            status = true;

            return null;
        }

    }







}