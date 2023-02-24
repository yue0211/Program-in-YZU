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
import android.text.InputType;
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




public class CalendarActivity extends AppCompatActivity {

    CircleImageView profile_image;
    TextView username;

    FirebaseUser firebaseUser;
    DatabaseReference reference;

    private TableLayout tab,tab2;

    public ArrayList<HashMap<String, String>> contactList, nContactList;

    private String TAG = CalendarActivity.class.getSimpleName();

    private Spinner spinner;

    private TextView reading;

    private boolean status;

    private static String url = "https://api.jsonstorage.net/v1/json/ed324453-ff9a-490e-b380-6b3f0bb931ae/f938fd06-ece7-4de7-b7b6-f34ebd399293";

    public ArrayList<HashMap<String, String>> week1,week2,week3,week4,week5,week6,week7;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_calendar);
        new CalendarActivity.GetContacts().execute();
        threadRun();

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setTitle("");


        contactList = new ArrayList<>();
        nContactList = new ArrayList<>();

        spinner =  findViewById(R.id.sp);
        reading =  findViewById(R.id.reading);

        status = false;

        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.weekValue, android.R.layout.simple_spinner_item);

        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        spinner.setAdapter(adapter);

        spinner.setOnItemSelectedListener(spnOnItemSelected);



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

    private void update(String week){

        for(int i = 0; i <contactList.size(); i++)
        {
            Log.e(TAG,contactList.get(i).get("update")+"測試");
            if(contactList.get(i).get("update").equals(week))
            {
                TableRow tbrow0 = new TableRow(CalendarActivity.this);
                TableRow.LayoutParams lp = new TableRow.LayoutParams(TableRow.LayoutParams.WRAP_CONTENT,TableRow.LayoutParams.WRAP_CONTENT);
                tbrow0.setLayoutParams(lp);

                TableRow.LayoutParams params = new TableRow.LayoutParams(0, ActionBar.LayoutParams.MATCH_PARENT,1);

                TextView tv0 = new TextView(CalendarActivity.this);
                tv0.setLayoutParams(params);
                tv0.setText(contactList.get(i).get("name"));
                tv0.setGravity(Gravity.LEFT);
                tv0.setTextAppearance(android.R.style.TextAppearance_Medium);
                tv0.setBackgroundResource(R.drawable.cell_shape);

                tv0.setInputType(InputType.TYPE_CLASS_TEXT |
                        InputType.TYPE_TEXT_FLAG_MULTI_LINE |
                        InputType.TYPE_TEXT_FLAG_CAP_SENTENCES);
                tv0.setMaxWidth(R.dimen.my_dimen);
                tv0.setMaxLines(50);
                tbrow0.addView(tv0);



                TextView tv1 = new TextView(CalendarActivity.this);
                tv1.setLayoutParams(params);
                tv1.setText(contactList.get(i).get("first"));
                tv1.setTextAppearance(android.R.style.TextAppearance_Medium);
                tv1.setBackgroundResource(R.drawable.cell_shape);
                tv1.setGravity(Gravity.CENTER);


                tv1.setInputType(InputType.TYPE_CLASS_TEXT |
                        InputType.TYPE_TEXT_FLAG_MULTI_LINE |
                        InputType.TYPE_TEXT_FLAG_CAP_SENTENCES);
                tv1.setMaxWidth(R.dimen.my_dimen);
                tv1.setMaxLines(50);
                tbrow0.addView(tv1);
                tab.addView(tbrow0);
            }
            else if(contactList.get(i).get("update").equals("時間未定"))
            {
                TableRow tbrow0 = new TableRow(CalendarActivity.this);
                TableRow.LayoutParams lp = new TableRow.LayoutParams(TableRow.LayoutParams.WRAP_CONTENT,TableRow.LayoutParams.WRAP_CONTENT);
                tbrow0.setLayoutParams(lp);

                TableRow.LayoutParams params = new TableRow.LayoutParams(0, ActionBar.LayoutParams.MATCH_PARENT,1);

                TextView tv0 = new TextView(CalendarActivity.this);
                tv0.setLayoutParams(params);
                tv0.setText(contactList.get(i).get("name"));
                tv0.setGravity(Gravity.LEFT);
                tv0.setTextAppearance(android.R.style.TextAppearance_Medium);
                tv0.setBackgroundResource(R.drawable.cell_shape);

                tv0.setInputType(InputType.TYPE_CLASS_TEXT |
                        InputType.TYPE_TEXT_FLAG_MULTI_LINE |
                        InputType.TYPE_TEXT_FLAG_CAP_SENTENCES);
                tv0.setMaxWidth(R.dimen.my_dimen);
                tv0.setMaxLines(50);
                tbrow0.addView(tv0);

                tab2.addView(tbrow0);
            }


        }

    }

    private AdapterView.OnItemSelectedListener spnOnItemSelected
            = new AdapterView.OnItemSelectedListener() {
        public void onItemSelected(AdapterView<?> parent, View view,
                                   int pos, long id) {
            String Position =String.valueOf(pos);
            String week =parent.getItemAtPosition(pos).toString();

            tab.removeViews(0, Math.max(0, tab.getChildCount()));
            tab2.removeViews(0, Math.max(0, tab2.getChildCount()));

            if(!contactList.isEmpty())
            {
                if(week.equals("週一"))
                    update("每週一");
                else if(week.equals("週二"))
                    update("每週二");
                else if(week.equals("週三"))
                    update("每週三");
                else if(week.equals("週四"))
                    update("每週四");
                else if(week.equals("週五"))
                    update("每週五");
                else if(week.equals("週六"))
                    update("每週六");
                else if(week.equals("週日"))
                    update("每週日");
            }


        }
        public void onNothingSelected(AdapterView<?> parent) {

        }
    };


    private void threadRun() {
        new Thread(() -> {
            for (int i = 1; i < 5; i++)
            {
                runOnUiThread(() -> {
                    if(status)
                    {
                        spinner.setVisibility(View.VISIBLE);
                        reading.setVisibility(View.GONE);
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
                    JSONArray contacts = jsonObj.getJSONArray("season");
                    Log.e(TAG, "season的尺寸 " + contacts.length());

                    for (int i = 0; i < contacts.length(); i++)
                    {
                        JSONObject c = contacts.getJSONObject(i);

                        String name = c.getString("name");
                        String first = c.getString("first");
                        String update = c.getString("update");

                        HashMap<String, String> contact = new HashMap<>();

                        contact.put("name", name);
                        contact.put("first", first);
                        contact.put("update", update);

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