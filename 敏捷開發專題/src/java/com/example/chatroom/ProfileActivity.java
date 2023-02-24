package com.example.chatroom;

import static android.app.Activity.RESULT_OK;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.ContentResolver;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.MimeTypeMap;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.resource.bitmap.RoundedCorners;
import com.bumptech.glide.request.RequestOptions;
import com.example.chatroom.Model.User;
import com.example.chatroom.R;
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

public class ProfileActivity extends AppCompatActivity {


    CircleImageView image_profile;
    ImageView image_oshi;
    TextView username, oshi_name, oshi_from, oshi_reason;

    DatabaseReference reference;
    FirebaseUser fuser;


    StorageReference storageReference;
    private static final int IMAGE_REQUEST = 1;
    private Uri imageUri;
    private StorageTask uploadTask;

    HashMap<String,Object> map = new HashMap<>();///
    User current_user;///
    Button save_profile;///
    String img_mode = "";



    @SuppressLint("WrongViewCast")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);




        image_profile = findViewById(R.id.profile_image);
        username = findViewById(R.id.username);

        oshi_name = findViewById(R.id.oshi_name_input);
        oshi_from = findViewById(R.id.oshi_from_input);
        oshi_reason = findViewById(R.id.oshi_reason_input);
        image_oshi = findViewById(R.id.oshi_imageURL);

        storageReference = FirebaseStorage.getInstance().getReference("uplaods");

        fuser = FirebaseAuth.getInstance().getCurrentUser();
        reference = FirebaseDatabase.getInstance().getReference("Users").child(fuser.getUid());

        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                User user = snapshot.getValue(User.class);
                assert user != null;
                username.setText(user.getUsername());

                oshi_name.setText(user.getOshi_name());
                oshi_from.setText(user.getOshi_from());
                oshi_reason.setText(user.getOshi_reason());



                current_user = user;///

                if(user.getImageURL().equals("default"))
                    image_profile.setImageResource(R.mipmap.ic_launcher_round);
                else
                {
                    if(!isDestroy((Activity)ProfileActivity.this)){
                        RoundedCorners roundedCorners = new RoundedCorners(20);
                        RequestOptions options = new RequestOptions().bitmapTransform(roundedCorners);
                        Glide.with(ProfileActivity.this).load((String) user.getImageURL()).apply(options).into(image_profile);
                    }
                }

                if(user.getOshi_imageURL() != null)
                    if(!user.getOshi_imageURL().equals("default"))
                    {
                        if(!isDestroy((Activity)ProfileActivity.this)){
                            RoundedCorners roundedCorners = new RoundedCorners(1);
                            RequestOptions options = new RequestOptions().bitmapTransform(roundedCorners);
                            Glide.with(ProfileActivity.this).load((String) user.getOshi_imageURL()).apply(options).into(image_oshi);
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

        image_oshi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                img_mode = "oshi";
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
                oshi_reason = findViewById(R.id.oshi_reason_input);

                map.put("username",username.getText().toString());
                map.put("search",username.getText().toString().toLowerCase());
                map.put("oshi_name",oshi_name.getText().toString());
                map.put("oshi_from",oshi_from.getText().toString());
                map.put("oshi_reason",oshi_reason.getText().toString());
                if(!map.isEmpty()) {
                    reference.updateChildren(map);
                    startActivity(new Intent(ProfileActivity.this,MainActivity2.class).setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP));
                }
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

        ContentResolver contentResolver = ProfileActivity.this.getContentResolver();
        MimeTypeMap mimeTypeMap = MimeTypeMap.getSingleton();
        return mimeTypeMap.getExtensionFromMimeType(contentResolver.getType(uri));

    }

    private void uploadImage(){

        final ProgressDialog pd = new ProgressDialog(ProfileActivity.this);
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

                        reference = FirebaseDatabase.getInstance().getReference("Users").child(fuser.getUid());
                        //HashMap<String,Object> map = new HashMap<>();

                        if(img_mode.equals("profile")) {
                            map.put("imageURL", mUri);

                            Glide.with(ProfileActivity.this).load(mUri).into(image_profile);///
                        }
                        else if(img_mode.equals("oshi")) {
                            map.put("oshi_imageURL", mUri);
                            Glide.with(ProfileActivity.this).load(mUri).into(image_oshi);///
                        }

                        pd.dismiss();
                    }
                    else{
                        Toast.makeText(ProfileActivity.this,"失敗",Toast.LENGTH_SHORT).show();
                        pd.dismiss();
                    }

                }

            }).addOnFailureListener(new OnFailureListener() {
                @Override
                public void onFailure(@NonNull Exception e) {

                    Toast.makeText(ProfileActivity.this,e.getMessage(),Toast.LENGTH_SHORT).show();
                    pd.dismiss();
                }
            });

        }
        else
            Toast.makeText(ProfileActivity.this,"沒有照片被選取",Toast.LENGTH_SHORT).show();

    }


    @Override
    public void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);


        if(requestCode == IMAGE_REQUEST && resultCode==RESULT_OK && data!=null && data.getData()!=null)
        {
            imageUri = data.getData();

            if(uploadTask!=null && uploadTask.isInProgress())
                Toast.makeText(ProfileActivity.this,"正在上傳中",Toast.LENGTH_SHORT).show();
            else
                uploadImage();

        }

    }






}