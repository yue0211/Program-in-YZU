package com.example.chatroom;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.ContentResolver;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.webkit.MimeTypeMap;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.resource.bitmap.RoundedCorners;
import com.bumptech.glide.request.RequestOptions;
import com.example.chatroom.Model.Group;
import com.example.chatroom.Model.User;
import com.google.android.gms.tasks.Continuation;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;
import com.google.firebase.storage.StorageTask;
import com.google.firebase.storage.UploadTask;

import java.util.HashMap;

import de.hdodenhof.circleimageview.CircleImageView;

public class GroupProfileActivity extends AppCompatActivity {



    CircleImageView image_profile;
    TextView username, oshi_name, oshi_from;

    DatabaseReference reference;
    //FirebaseUser fuser;


    StorageReference storageReference;
    private static final int IMAGE_REQUEST = 1;
    private Uri imageUri;
    private StorageTask uploadTask;

    Group current_user;///
    Button save_profile;///
    String img_mode = "";


    Intent intent;
    String userid;

    @SuppressLint("WrongViewCast")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_group_profile);

        intent = getIntent();
        userid = intent.getStringExtra("userid");



        image_profile = findViewById(R.id.profile_image);
        username = findViewById(R.id.username);

        oshi_name = findViewById(R.id.oshi_name_input);
        oshi_from = findViewById(R.id.oshi_from_input);

        storageReference = FirebaseStorage.getInstance().getReference("uplaods");

        reference = FirebaseDatabase.getInstance().getReference("Groups").child(userid);

        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                //Group user = snapshot.getValue(Group.class);
                //assert user != null;
                username.setText(snapshot.child("Name").getValue().toString());

                oshi_name.setText(snapshot.child("oshi_name").getValue().toString());
                oshi_from.setText(snapshot.child("oshi_from").getValue().toString());


                if(snapshot.child("pic").getValue().toString().equals("default"))
                    image_profile.setImageResource(R.mipmap.ic_launcher_round);
                else
                {
                    if(!isDestroy((Activity)GroupProfileActivity.this)){
                        RoundedCorners roundedCorners = new RoundedCorners(20);
                        RequestOptions options = new RequestOptions().bitmapTransform(roundedCorners);
                        Glide.with(GroupProfileActivity.this).load((String) snapshot.child("pic").getValue().toString()).apply(options).into(image_profile);
                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        image_profile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                img_mode = "profile";
                openImage();
            }
        });

        save_profile = findViewById(R.id.save_profile);

        save_profile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                username = findViewById(R.id.username);
                oshi_name = findViewById(R.id.oshi_name_input);
                oshi_from = findViewById(R.id.oshi_from_input);
                if(username.getText().toString().equals("")){
                    Toast.makeText(GroupProfileActivity.this,"名稱不可為空",Toast.LENGTH_SHORT).show();
                    return;
                }
                reference.child("Name").setValue(username.getText().toString());
                reference.child("oshi_name").setValue(oshi_name.getText().toString());
                reference.child("oshi_from").setValue(oshi_from.getText().toString());
                finish();
            }
        });

    }

    public static boolean isDestroy(Activity mActivity) {
        if (mActivity== null || mActivity.isFinishing() || (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1 && mActivity.isDestroyed())) {
            return true;
        } else {
            return false;
        }
    }


    private void openImage() {
        Intent intent = new Intent();
        intent.setType("image/*");
        intent.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(intent,IMAGE_REQUEST);
    }

    private String getFileExtension(Uri uri){

        ContentResolver contentResolver = GroupProfileActivity.this.getContentResolver();
        MimeTypeMap mimeTypeMap = MimeTypeMap.getSingleton();
        return mimeTypeMap.getExtensionFromMimeType(contentResolver.getType(uri));

    }

    private void uploadImage(){

        final ProgressDialog pd = new ProgressDialog(GroupProfileActivity.this);
        pd.setMessage("上傳中");
        pd.show();

        if(imageUri!=null)
        {
            final StorageReference fileReference = storageReference.child(System.currentTimeMillis()+"."+getFileExtension(imageUri));

            uploadTask = fileReference.putFile(imageUri);

            uploadTask.continueWithTask(new Continuation<UploadTask.TaskSnapshot, Task<Uri>>() {
                @Override
                public Task<Uri> then(@NonNull Task<UploadTask.TaskSnapshot> task) throws Exception {

                    if(!task.isSuccessful())
                        throw task.getException();

                    return  fileReference.getDownloadUrl();
                }
            }).addOnCompleteListener(new OnCompleteListener<Uri>() {
                @Override
                public void onComplete(@NonNull Task<Uri> task) {

                    if(task.isSuccessful())
                    {
                        Uri downloadUri = task.getResult();
                        String mUri = downloadUri.toString();

                        reference = FirebaseDatabase.getInstance().getReference("Groups").child(userid);
                        //HashMap<String,Object> map = new HashMap<>();

                        if(img_mode.equals("profile")) {
                            reference.child("pic").setValue(mUri);

                            Glide.with(GroupProfileActivity.this).load(mUri).into(image_profile);///
                        }

                        pd.dismiss();
                    }
                    else{
                        Toast.makeText(GroupProfileActivity.this,"失敗",Toast.LENGTH_SHORT).show();
                        pd.dismiss();
                    }

                }

            }).addOnFailureListener(new OnFailureListener() {
                @Override
                public void onFailure(@NonNull Exception e) {

                    Toast.makeText(GroupProfileActivity.this,e.getMessage(),Toast.LENGTH_SHORT).show();
                    pd.dismiss();
                }
            });

        }
        else
            Toast.makeText(GroupProfileActivity.this,"沒有照片被選取",Toast.LENGTH_SHORT).show();

    }


    @Override
    public void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);


        if(requestCode == IMAGE_REQUEST && resultCode==RESULT_OK && data!=null && data.getData()!=null)
        {
            imageUri = data.getData();

            if(uploadTask!=null && uploadTask.isInProgress())
                Toast.makeText(GroupProfileActivity.this,"正在上傳中",Toast.LENGTH_SHORT).show();
            else
                uploadImage();

        }

    }
}