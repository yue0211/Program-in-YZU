package com.example.chatroom;

import android.content.ContentResolver;
import android.net.Uri;
import android.os.Bundle;
import android.util.Pair;
import android.view.KeyEvent;
import android.view.View;
import android.webkit.MimeTypeMap;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.example.chatroom.Model.Chat;
import com.google.android.gms.tasks.Continuation;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;
import com.google.firebase.storage.UploadTask;
import com.squareup.picasso.Picasso;

import java.time.OffsetDateTime;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;

public class SendImage extends AppCompatActivity {
    String url,sender,receiver;
    ImageView imageView;
    boolean isgroup;
    Uri imageurl;
    ProgressBar progressBar;
    Button button;
//    TextView textView;
    UploadTask uploadTask;
    StorageReference storageReference;
    FirebaseStorage firebaseStorage;

    Chat messageMember;
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {//捕捉返回鍵
        if ((keyCode == KeyEvent.KEYCODE_BACK)) {
            SendImage.this.finish();//關閉activity
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_send_image);

        messageMember = new Chat();

        storageReference = firebaseStorage.getInstance().getReference("Message Images");

        imageView=findViewById(R.id.iv_sendImage);
        button=findViewById(R.id.btn_sendimage);
        progressBar=findViewById(R.id.pb_sendImade);
//        textView=findViewById(R.id.tv_dont);

        Bundle bundle = getIntent().getExtras();
        if(bundle!=null){
            url=bundle.getString("u");
            receiver=bundle.getString("ruid");
            sender=bundle.getString("suid");
            isgroup=bundle.getBoolean("group");
        }else{
            Toast.makeText(this, "錯誤", Toast.LENGTH_SHORT).show();
        }

        Picasso.get().load(url).into(imageView);
        imageurl = Uri.parse(url);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendImage();
//                textView.setVisibility(View.VISIBLE);
            }

            private String getFileExt(Uri uri){
                ContentResolver contentResolver = getContentResolver();
                MimeTypeMap mimeTypeMap = MimeTypeMap.getSingleton();
                return mimeTypeMap.getExtensionFromMimeType(contentResolver.getType(uri));
            }
            private Pair<String, String> getTime(int timeZone){
                DateTimeFormatter t1 = DateTimeFormatter.ofPattern("uuuu'/'MM'/'dd");
                DateTimeFormatter t2 = DateTimeFormatter.ofPattern("HH:mm:ss");

                ZoneOffset offset = ZoneOffset.ofHours( timeZone );
                OffsetDateTime odt = OffsetDateTime.now( offset );
                String t1s = odt.format( t1 ), t2s = odt.format( t2 );

                Pair<String, String> tpair = new Pair<>(t1s, t2s);
                return tpair;
            }


            private void sendImage() {
                if(imageurl!=null){
                    progressBar.setVisibility(View.VISIBLE);
                    final StorageReference reference = storageReference.child(System.currentTimeMillis()+"."+getFileExt(imageurl));
                    uploadTask=reference.putFile(imageurl);

                    Task<Uri> uriTask = uploadTask.continueWithTask(new Continuation<UploadTask.TaskSnapshot, Task<Uri>>() {
                        @Override
                        public Task<Uri> then(@NonNull Task<UploadTask.TaskSnapshot> task) throws Exception {
                            if(!task.isSuccessful()){
                                throw task.getException();
                            }
                            return reference.getDownloadUrl();
                        }
                    }).addOnCompleteListener(new OnCompleteListener<Uri>() {
                        @Override
                        public void onComplete(@NonNull Task<Uri> task) {
                            if(task.isSuccessful()){
                                Uri downloadUri = task.getResult();
                                progressBar.setVisibility(View.INVISIBLE);
//                                textView.setVisibility(View.INVISIBLE);

                                DatabaseReference reference = FirebaseDatabase.getInstance().getReference();
                                if(isgroup){
                                    reference = FirebaseDatabase.getInstance().getReference("Groups").child(receiver);
                                }


                                Pair<String, String> TimePair = getTime( 8 );
                                String Date = TimePair.first;
                                String Time = TimePair.second;



                                HashMap<String,Object> hashMap = new HashMap<>();
                                hashMap.put("sender", sender);
                                hashMap.put("receiver", receiver);
                                hashMap.put("message", downloadUri.toString());
                                hashMap.put("isseen",false);
                                hashMap.put("date",Date);
                                hashMap.put("Time",Time);
                                hashMap.put("type","iv");
                                hashMap.put("userCantSee","");

                                hashMap.put("emoji_smile","");
                                hashMap.put("emoji_love","");
                                hashMap.put("emoji_cry","");
                                hashMap.put("emoji_angry","");
                                hashMap.put("emoji_nothing","");
                                hashMap.put("emoji_good","");
                                reference.child("Chats").push().setValue(hashMap);

                                if(!isgroup){

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
                                }
                                SendImage.this.finish();
                            }
                        }
                    });
                }else{
                    Toast.makeText(SendImage.this, "請選擇圖片", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

}
