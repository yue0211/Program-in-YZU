package com.example.chatroom;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.ProgressDialog;
import android.app.assist.AssistStructure;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Parcelable;
import android.provider.MediaStore;
import android.util.Log;
import android.util.Pair;
import android.view.View;
import android.widget.EditText;
import android.widget.HorizontalScrollView;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.EmojiCompatConfigurationView;
import androidx.appcompat.widget.Toolbar;
import androidx.core.app.ActivityCompat;
import androidx.core.content.res.ResourcesCompat;
import androidx.emoji.bundled.BundledEmojiCompatConfig;
import androidx.emoji.text.EmojiCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.example.chatroom.Adapter.MessageAdapter;
import com.example.chatroom.Fragments.APIService;
import com.example.chatroom.Model.Chat;
import com.example.chatroom.Model.User;
import com.example.chatroom.Notifications.Client;
import com.example.chatroom.Notifications.Data;
import com.example.chatroom.Notifications.MyResponse;
import com.example.chatroom.Notifications.Sender;
import com.example.chatroom.Notifications.Token;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.time.OffsetDateTime;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import de.hdodenhof.circleimageview.CircleImageView;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class MessageActivity extends AppCompatActivity {
    private boolean isPermissionPassed = false;
    /**
     * 取得將檔案寫入手機的權限
     */
    private void getPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M &&
                ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                        != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(
                    this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 100);
        } else {
            isPermissionPassed = true;
        }
    }

    /**
     * 回傳使用者所做的權限選擇(接受/拒絕)
     */
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == 100) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                /**如果用戶同意*/
                isPermissionPassed = true;
            } else {
                /**如果用戶不同意*/
                if (ActivityCompat.shouldShowRequestPermissionRationale(this
                        , Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                    Toast.makeText(this, "正因為如此你沒資格啊", Toast.LENGTH_SHORT).show();
                    getPermission();
                }
            }
        }
    }//onRequestPermissionsResult

    private static final int PICK_IMAGE = 1;
    private static RecyclerView _recyclerView;

    CircleImageView profile_image;
    TextView username;

    FirebaseUser fuser;
    DatabaseReference reference;
    DatabaseReference ureference;
    DatabaseReference breference;


    RelativeLayout bottom;
    ImageButton btn_send;
    ImageButton btn_send_picturen;
    EditText text_send;
    MessageAdapter messageAdapter;
    List<Chat> mChat;

    RecyclerView recyclerView;

    Intent intent;

    ValueEventListener seenListener;

    String userid;
    String CHAT_ROBOT_ID = "8Xb9aoMJrKQTX7xEXDTYzKQr6da2";

    APIService apiService;

    boolean notify = false, readerIsRobot = false;

    User currentUser = new User("", "", "", "", "", "");
    User botUser = new User("", "", "", "", "", "");
    Uri uri;

    private String TAG = MessageActivity.class.getSimpleName();

    private long last_message_number = 0;

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode == PICK_IMAGE && resultCode==RESULT_OK && data!=null&&data.getData()!=null){
            Log.e(TAG,data.toString());
            uri = data.getData();

            Intent intent = new Intent(MessageActivity.this,SendImage.class);
            intent.putExtra("u",uri.toString());
            intent.putExtra("ruid",userid);
            intent.putExtra("suid",fuser.getUid());
            intent.putExtra("group",false);
            startActivity(intent);

        }else{
//            Toast.makeText(this,"No file selected", Toast.LENGTH_SHORT).show();
        }

    }

    @SuppressLint("CutPasteId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_message);


        EmojiCompat.Config config = new BundledEmojiCompatConfig(this);
        EmojiCompat.init(config);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setTitle("");
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MessageActivity.this,MainActivity2.class).setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP));
            }
        });

        apiService = Client.getClient("https://fcm.googleapis.com").create(APIService.class);

        recyclerView = findViewById(R.id.recycler_view);
        _recyclerView = findViewById(R.id.recycler_view);
        recyclerView.setHasFixedSize(true);
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(getApplicationContext());
        linearLayoutManager.setStackFromEnd(true);
        recyclerView.setLayoutManager(linearLayoutManager);



        profile_image = findViewById(R.
                id.profile_image);
        username = findViewById(R.id.username);
        btn_send = findViewById(R.id.btn_send);
        btn_send_picturen = findViewById(R.id.btn_send_picture);

        text_send = findViewById(R.id.text_send);
        bottom = findViewById(R.id.bottom);

        intent = getIntent();
        userid = intent.getStringExtra("userid");
        fuser = FirebaseAuth.getInstance().getCurrentUser();


        ureference = FirebaseDatabase.getInstance().getReference("Users").child(fuser.getUid());

        ureference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Log.e(TAG,"幼女最高");
                User user = snapshot.getValue(User.class);
                assert user != null;
                currentUser = user;
                Log.e(TAG,"//////////currentUser.getId():"+currentUser.getId()+"////////////////");

            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });
        Log.e(TAG,"1#####currentUser.getId():"+currentUser.getId()+"#####");

        btn_send_picturen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MessagegClear();
                EmojiClear();
                Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
                intent.addCategory(Intent.CATEGORY_OPENABLE);
                intent.setType("image/*");
                startActivityForResult(Intent.createChooser(intent, "選擇圖片"), PICK_IMAGE);
            }
        });

        text_send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MessagegClear();
                EmojiClear();}
        });

        bottom.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MessagegClear();
                EmojiClear();}
        });


        text_send.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                MessagegClear();
                EmojiClear();

                ClipboardManager myClipboard = (ClipboardManager)getSystemService(CLIPBOARD_SERVICE);

                ClipData.Item item = myClipboard.getPrimaryClip().getItemAt(0);

                String message = item.getText().toString();

                text_send.setText(text_send.getText()+message);

                return true;
            }
        });


        btn_send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                MessagegClear();
                EmojiClear();

                notify = true;

                String msg = text_send.getText().toString();

                if(!msg.equals(""))
                    sendMessage(fuser.getUid(),userid,msg);
                else
                    Toast.makeText(MessageActivity.this,"無法傳送此訊息",Toast.LENGTH_SHORT).show();

                text_send.setText("");

            }

        });


        if(userid != null)
            reference = FirebaseDatabase.getInstance().getReference("Users").child(userid);

        if(userid != null)
            reference.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    User user = snapshot.getValue(User.class);
                    username.setText(user.getUsername());

                    if(user.getImageURL().equals("default"))
                        profile_image.setImageResource(R.mipmap.ic_launcher);
                    else
                        Glide.with(getApplicationContext()).load(user.getImageURL()).into(profile_image);

                    Log.d(TAG, "監聽5");
                    readMessage(fuser.getUid(),userid,user.getImageURL());
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {

                }
            });

        seenMessage(userid);
        getPermission();

    }

    public static void MessagegClear()
    {
        for(int i = 0; i < _recyclerView.getChildCount(); i++)
        {
            RecyclerView.ViewHolder holder = _recyclerView.getChildViewHolder(_recyclerView.getChildAt(i));
            holder.itemView.findViewById(R.id.choice).setVisibility(View.GONE);
        }
    }

    public static void EmojiClear()
    {
        for(int i = 0; i < _recyclerView.getChildCount(); i++)
        {
            RecyclerView.ViewHolder holder = _recyclerView.getChildViewHolder(_recyclerView.getChildAt(i));
            holder.itemView.findViewById(R.id.top).setVisibility(View.GONE);
        }
    }

    private void seenMessage(String userid){
        Log.d(TAG, "看三小");
        reference = FirebaseDatabase.getInstance().getReference("Chats");
        seenListener = reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                {

                    Chat chat = dataSnapshot.getValue(Chat.class);

                    if(fuser != null)
                        if(chat.getReceiver().equals(fuser.getUid()) && chat.getSender().equals(userid))
                        {
                            HashMap<String,Object>hashMap = new HashMap<>();
                            hashMap.put("isseen",true);
                            dataSnapshot.getRef().updateChildren(hashMap);
                        }

                }


            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        breference = FirebaseDatabase.getInstance().getReference("Users").child(userid);

        breference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                User user = snapshot.getValue(User.class);
                assert user != null;
                if(!user.getId().equals(CHAT_ROBOT_ID))
                    botUser = user;

            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });



    }

    public Pair<String, String> getTime(int timeZone){
        DateTimeFormatter t1 = DateTimeFormatter.ofPattern("uuuu'/'MM'/'dd");
        DateTimeFormatter t2 = DateTimeFormatter.ofPattern("HH:mm:ss");

        ZoneOffset offset = ZoneOffset.ofHours( timeZone );
        OffsetDateTime odt = OffsetDateTime.now( offset );
        String t1s = odt.format( t1 ), t2s = odt.format( t2 );

        Pair<String, String> tpair = new Pair<>(t1s, t2s);
        return tpair;
    }





    public void sendMessage(String sender,String receiver, String message) {
        Log.d(TAG, "sendMessage");
        DatabaseReference reference = FirebaseDatabase.getInstance().getReference();


        Pair<String, String> TimePair = getTime( 8 );
        String Date = TimePair.first;
        String Time = TimePair.second;


        HashMap<String,Object> hashMap = new HashMap<>();
        hashMap.put("sender", sender);
        hashMap.put("receiver", receiver);
        hashMap.put("message", message);
        hashMap.put("isseen",false);
        hashMap.put("date",Date);
        hashMap.put("Time",Time);
        hashMap.put("type","text");

        hashMap.put("userCantSee","");

        hashMap.put("emoji_smile","");
        hashMap.put("emoji_love","");
        hashMap.put("emoji_cry","");
        hashMap.put("emoji_angry","");
        hashMap.put("emoji_nothing","");
        hashMap.put("emoji_good","");

        reference.child("Chats").push().setValue(hashMap);


        DatabaseReference chatRef = FirebaseDatabase.getInstance().getReference("Chatlist")
                .child(sender)
                .child(receiver);
        DatabaseReference chatRef2 = FirebaseDatabase.getInstance().getReference("Chatlist")//
                .child(receiver)
                .child(sender);

        chatRef.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if(!snapshot.exists())
                {
                    chatRef.child("id").setValue(receiver);
                    chatRef2.child("id").setValue(sender);//
                }

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        final String msg = message;

        if(fuser != null)
            reference = FirebaseDatabase.getInstance().getReference("Users").child(fuser.getUid());
        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Log.d(TAG, "通知");
                User user = snapshot.getValue(User.class);
                if(notify)
                    sendNotification(receiver,user.getUsername(),msg);


                notify = false;
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        Log.d(TAG, "sendMessage結尾");

    }



    private void sendNotification(String receiver,String username, String message)
    {
        DatabaseReference tokens = FirebaseDatabase.getInstance().getReference("Tokens");
        Query query = tokens.orderByKey().equalTo(receiver);

        query.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                {
                    Token token = dataSnapshot.getValue(Token.class);
                    Data data = new Data(fuser.getUid(),R.mipmap.ic_launcher,username+": "+message,"新訊息",userid);

                    Sender sender = new Sender(data,token.getToken());

                    apiService.sendNotification(sender)
                            .enqueue(new Callback<MyResponse>() {
                                @Override
                                public void onResponse(Call<MyResponse> call, Response<MyResponse> response) {

                                    if(response.code()==200)
                                        if(response.body().success!=1)
                                            Toast.makeText(MessageActivity.this,"失敗",Toast.LENGTH_SHORT).show();
                                }

                                @Override
                                public void onFailure(Call<MyResponse> call, Throwable t) {
                                }
                            });
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });
    }


    private void readMessage(String myid,String userid,String imageurl) {

        mChat = new ArrayList<>();


        DatabaseReference ReadMessageReference = FirebaseDatabase.getInstance().getReference("Chats");

        ReadMessageReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                mChat.clear();
                String emptys = new String("");
                Boolean emptyb = Boolean.FALSE;

                Chat chat = new Chat(emptys , emptys, emptys,  emptyb, emptys, emptys);

                long current_message_number = 0;

                for(DataSnapshot dataSnapshot:snapshot.getChildren())
                    current_message_number++;

                for(DataSnapshot dataSnapshot:snapshot.getChildren())
                {
                    chat = dataSnapshot.getValue(Chat.class);
                    if(chat.getReceiver().equals(myid) && chat.getSender().equals(userid)|| chat.getReceiver().equals(userid) && chat.getSender().equals(myid))
                    {
                        if(!chat.getMessage().equals("") && !chat.getUserCantSee().contains(fuser.getUid()))
                            mChat.add(chat);
                        if(chat.getMessage().equals(""))
                        {
                            Chat chat_copy = chat;
                            chat_copy.setMessage("這則訊息已被收回");
                            mChat.add(chat_copy);
                        }
                    }

                    if(!(current_message_number > last_message_number)) {
                        Parcelable savedRecyclerLayoutState = recyclerView.getLayoutManager().onSaveInstanceState();
                        recyclerView.getLayoutManager().onRestoreInstanceState(savedRecyclerLayoutState);
                    }

                    messageAdapter = new MessageAdapter(MessageActivity.this,mChat,imageurl);
                    recyclerView.setAdapter(messageAdapter);

                    Log.e(TAG,"Activity:"+MessageAdapter.holderPosition);

                }

                last_message_number = current_message_number;
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }

        });

    }


    private void status(String status){
        if(fuser != null)
            ureference = FirebaseDatabase.getInstance().getReference("Users").child(fuser.getUid());

        HashMap<String,Object> hashMap = new HashMap<>();
        hashMap.put("status",status);

        ureference.updateChildren(hashMap);
    }


    @Override
    protected void onResume() {
        super.onResume();
        status("online");
    }

    @Override
    protected void onPause() {
        super.onPause();
        reference.removeEventListener(seenListener);
        status("offline");
    }







    //檢查完是否為合法狀態再進來 先在外面更新完狀態
    private Pair< Boolean, String > robotMessage(String userState, String userInput)
    {
        Pair< Boolean, String > robotReturnMessage;

        Boolean realMess = Boolean.TRUE;
        String robotMessage = "";
        String question = "請輸入數字選項 : \n";
        String errInput = "輸入錯誤 請重新輸入";

        switch (userState)
        {
            case "0":
                robotMessage += "親愛的用戶您好 :\n" +
                                "歡迎來到肥宅聊天室，此機器人會不定時公告官方資訊。";
                break;
        }

        robotReturnMessage = new Pair<>(realMess, robotMessage);
        return robotReturnMessage;
    }

    public void rbtMessInit(String userid, String state)
    {
        String robotMessage = robotMessage(state, "").second;
        sendMessage(CHAT_ROBOT_ID, userid, robotMessage);
    }
}