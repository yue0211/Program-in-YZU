package com.example.chatroom;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.app.ActivityCompat;
import androidx.emoji.bundled.BundledEmojiCompatConfig;
import androidx.emoji.text.EmojiCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Parcelable;
import android.text.TextUtils;
import android.util.Log;
import android.util.Pair;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.example.chatroom.Adapter.GroupMessageAdapter;
import com.example.chatroom.Adapter.MessageAdapter;
import com.example.chatroom.Fragments.APIService;
import com.example.chatroom.Fragments.GroupFragment;
import com.example.chatroom.Model.Chat;
import com.example.chatroom.Model.User;
import com.example.chatroom.Notifications.Client;
import com.example.chatroom.Notifications.Data;
import com.example.chatroom.Notifications.MyResponse;
import com.example.chatroom.Notifications.Sender;
import com.example.chatroom.Notifications.Token;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.bottomsheet.BottomSheetDialog;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

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

public class GroupActivity extends AppCompatActivity {
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
    EditText search_users;
    private BottomSheetDialog bottomSheetDialog;
    CircleImageView profile_image;
    TextView username;

    FirebaseUser fuser;
    DatabaseReference reference;
    DatabaseReference ureference;
    //DatabaseReference breference;


    RelativeLayout bottom;
    ImageButton btn_send;
    ImageButton btn_send_picturen;
    ImageButton btn_add;
    EditText text_send;
    GroupMessageAdapter messageAdapter;
    List<Chat> mChat;

    RecyclerView recyclerView;

    Intent intent;

    ValueEventListener seenListener;

    String groupid;

    APIService apiService;

    boolean notify = false, readerIsRobot = false;

    User currentUser = new User("", "", "", "", "", "");
    Uri uri;

    private String TAG = GroupActivity.class.getSimpleName();

    private long last_message_number = 0;

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode == PICK_IMAGE && resultCode==RESULT_OK && data!=null&&data.getData()!=null){
            Log.e(TAG,data.toString());
            uri = data.getData();

            Intent intent = new Intent(GroupActivity.this,SendImage.class);
            intent.putExtra("u",uri.toString());
            intent.putExtra("ruid",groupid);
            intent.putExtra("suid",fuser.getUid());
            intent.putExtra("group",true);
            startActivity(intent);

        }else{
//            Toast.makeText(this,"No file selected", Toast.LENGTH_SHORT).show();
        }

    }

    @SuppressLint("CutPasteId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_group);


        EmojiCompat.Config config = new BundledEmojiCompatConfig(this);
        EmojiCompat.init(config);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setTitle("");
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GroupActivity.this.finish();
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
        btn_add=findViewById(R.id.btn_add);

        text_send = findViewById(R.id.text_send);
        bottom = findViewById(R.id.bottom);

        intent = getIntent();
        groupid = intent.getStringExtra("userid");
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
                    sendMessage(fuser.getUid(),groupid,msg);
                else
                    Toast.makeText(GroupActivity.this,"無法傳送此訊息",Toast.LENGTH_SHORT).show();

                text_send.setText("");

            }

        });

        btn_add.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                showBottomSheetDialog();
            }

        });

        if(groupid != null)
            reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid);

        if(groupid != null)
            reference.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    username.setText(snapshot.child("Name").getValue().toString()+"("+ snapshot.child("Users").getChildrenCount() +")");

                    if(snapshot.child("pic").getValue().toString().equals("default"))
                        profile_image.setImageResource(R.mipmap.ic_launcher);
                    else
                        Glide.with(getApplicationContext()).load(snapshot.child("pic").getValue().toString()).into(profile_image);

                    Log.d(TAG, "監聽5");
                    readMessage(fuser.getUid(),groupid);
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {

                }
            });

        seenMessage(groupid);
        getPermission();

    }

    private void showBottomSheetDialog() {

        bottomSheetDialog = new BottomSheetDialog(GroupActivity.this);
        bottomSheetDialog.setContentView(R.layout.bottom_sheet_dialog_add_layout);

        search_users = bottomSheetDialog.findViewById(R.id.search_users);

        btn_send = bottomSheetDialog.findViewById(R.id.btn_send);


        btn_send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                String addname=search_users.getText().toString();
                if(TextUtils.isEmpty(addname)){
                    Toast.makeText(GroupActivity.this,"名稱不得為空",Toast.LENGTH_SHORT).show();
                }else{
                    AddNewMem(addname);
                }
            }

        });

        bottomSheetDialog.show();

    }

    private void AddNewMem(String addname) {
        FirebaseUser fuser = FirebaseAuth.getInstance().getCurrentUser();
        reference = FirebaseDatabase.getInstance().getReference().child("Users");
        reference.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                final String[] id = {"",""};
                if(snapshot.exists())
                {
                    for (DataSnapshot postSnapshot: snapshot.getChildren()) {
                        if(addname.equals(postSnapshot.child("email").getValue().toString())){
                            id[0] =postSnapshot.child("id").getValue().toString();
                            id[1] =postSnapshot.child("username").getValue().toString();
                            break;
                        }
                    }
                }
                if(id[0].equals("")){
                    Toast.makeText(GroupActivity.this,"查無此帳號",Toast.LENGTH_SHORT).show();
                    return;
                }
                DatabaseReference buf=FirebaseDatabase.getInstance().getReference().child("Groups").child(groupid).child("Users");
                buf.addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot1) {
                        for (DataSnapshot postSnapshot: snapshot1.getChildren()) {
                            if(postSnapshot.getValue().toString().equals(id[0])) {
                                Toast.makeText(GroupActivity.this, id[1] + "已在群組", Toast.LENGTH_SHORT).show();
                                return;
                            }
                        }
                        buf.push().setValue(id[0]).addOnCompleteListener(new OnCompleteListener<Void>() {
                            @Override
                            public void onComplete(@NonNull Task<Void> task) {
                                if(task.isSuccessful()){
                                    Toast.makeText(GroupActivity.this,id[1]+"已加入群組",Toast.LENGTH_SHORT).show();
                                    bottomSheetDialog.setDismissWithAnimation(true);
                                    bottomSheetDialog.dismiss();
                                }
                            }
                        });
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {}
                });
            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {}
        });
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
        DatabaseReference reference1 = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
        reference1.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                {

                    Chat chat = dataSnapshot.getValue(Chat.class);
                    if(fuser != null)
                        if(!chat.getSender().equals(fuser.getUid()))
                        {
                            Log.d(TAG, chat.getSender());
                            Log.d(TAG, fuser.getUid());
                            HashMap<String,Object> hashMap = new HashMap<>();
                            hashMap.put("isseen",true);
                            dataSnapshot.getRef().updateChildren(hashMap);
                        }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });/*
        seenListener = reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                {

                    Chat chat = dataSnapshot.getValue(Chat.class);
                    if(fuser != null)
                        if(!chat.getSender().equals(fuser.getUid()))
                        {
                            Log.d(TAG, chat.getSender());
                            Log.d(TAG, fuser.getUid());
                            HashMap<String,Object> hashMap = new HashMap<>();
                            hashMap.put("isseen",true);
                            dataSnapshot.getRef().updateChildren(hashMap);
                        }
                }


            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });*/
/*
        breference = FirebaseDatabase.getInstance().getReference("Users").child(userid);

        breference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                User user = snapshot.getValue(User.class);
                assert user != null;

            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });
*/


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
        DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(receiver);


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

        final String msg = message;

        if(fuser != null)
            reference = FirebaseDatabase.getInstance().getReference("Users").child(fuser.getUid());
        reference.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Log.d(TAG, "通知");
                User user = snapshot.getValue(User.class);
                if(notify){
                    DatabaseReference noty = FirebaseDatabase.getInstance().getReference("Groups").child(receiver).child("Users");
                    noty.addListenerForSingleValueEvent(new ValueEventListener() {
                        @Override
                        public void onDataChange(@NonNull DataSnapshot snapshot1) {
                            for(DataSnapshot snapshotnoty:snapshot1.getChildren()){
                                if(!snapshotnoty.getValue().toString().equals(fuser.getUid()))
                                    sendNotification(snapshotnoty.getValue().toString(),user.getUsername(),msg);
                            }
                        }

                        @Override
                        public void onCancelled(@NonNull DatabaseError error) {

                        }
                    });
                }


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
                    Data data = new Data(fuser.getUid(),R.mipmap.ic_launcher,username+": "+message,"新訊息",receiver);

                    Sender sender = new Sender(data,token.getToken());

                    apiService.sendNotification(sender)
                            .enqueue(new Callback<MyResponse>() {
                                @Override
                                public void onResponse(Call<MyResponse> call, Response<MyResponse> response) {

                                    if(response.code()==200)
                                        if(response.body().success!=1)
                                            Toast.makeText(GroupActivity.this,"失敗",Toast.LENGTH_SHORT).show();
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


    private void readMessage(String myid,String groupid) {

        mChat = new ArrayList<>();


        DatabaseReference ReadMessageReference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
        ReadMessageReference.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                mChat.clear();
                String emptys = new String("");
                Boolean emptyb = Boolean.FALSE;

                Chat chat = new Chat(emptys , emptys, emptys,  emptyb, emptys, emptys);

                long current_message_number = snapshot.getChildrenCount();

                for(DataSnapshot dataSnapshot:snapshot.getChildren())
                {
                    chat = dataSnapshot.getValue(Chat.class);
                    if(chat.getMessage().equals(""))
                    {
                        Chat chat_copy = chat;
                        chat_copy.setMessage("這則訊息已被收回");
                        mChat.add(chat_copy);
                    }else if(!chat.getUserCantSee().contains(fuser.getUid()))
                        mChat.add(chat);
                    if(!(current_message_number > last_message_number)) {
                        Parcelable savedRecyclerLayoutState = recyclerView.getLayoutManager().onSaveInstanceState();
                        recyclerView.getLayoutManager().onRestoreInstanceState(savedRecyclerLayoutState);
                    }

                    messageAdapter = new GroupMessageAdapter(GroupActivity.this,mChat,groupid);
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
}