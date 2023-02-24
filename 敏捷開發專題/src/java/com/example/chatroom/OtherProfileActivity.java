package com.example.chatroom;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.resource.bitmap.RoundedCorners;
import com.bumptech.glide.request.RequestOptions;
import com.example.chatroom.Model.User;
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

import java.util.HashMap;

import de.hdodenhof.circleimageview.CircleImageView;

public class OtherProfileActivity extends AppCompatActivity {


    CircleImageView image_profile;
    ImageView image_oshi;
    TextView username, oshi_name, oshi_from, oshi_reason;

    DatabaseReference reference;
    FirebaseUser fuser;


    StorageReference storageReference;

    User current_user;///
    Button _return;///

    Intent intent;

    String userid;



    @SuppressLint("WrongViewCast")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_other_profile);


        intent = getIntent();
        userid = intent.getStringExtra("userid");


        image_profile = findViewById(R.id.profile_image);
        username = findViewById(R.id.username);

        oshi_name = findViewById(R.id.oshi_name_input);
        oshi_from = findViewById(R.id.oshi_from_input);
        oshi_reason = findViewById(R.id.oshi_reason_input);
        image_oshi = findViewById(R.id.oshi_imageURL);

        storageReference = FirebaseStorage.getInstance().getReference("uplaods");

        fuser = FirebaseAuth.getInstance().getCurrentUser();
        reference = FirebaseDatabase.getInstance().getReference("Users").child(userid);

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
                    if(!isDestroy((Activity)OtherProfileActivity.this)){
                        RoundedCorners roundedCorners = new RoundedCorners(20);
                        RequestOptions options = new RequestOptions().bitmapTransform(roundedCorners);
                        Glide.with(OtherProfileActivity.this).load((String) user.getImageURL()).apply(options).into(image_profile);
                    }
                }

                if(user.getOshi_imageURL() != null)
                    if(user.getOshi_imageURL().equals("default"))
                        image_oshi.setImageResource(R.mipmap.ic_launcher);
                    else
                    {
                        if(!isDestroy((Activity)OtherProfileActivity.this)){
                            RoundedCorners roundedCorners = new RoundedCorners(1);
                            RequestOptions options = new RequestOptions().bitmapTransform(roundedCorners);
                            Glide.with(OtherProfileActivity.this).load((String) user.getOshi_imageURL()).apply(options).into(image_oshi);
                        }
                    }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });




        _return = findViewById(R.id._return);

        _return.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(OtherProfileActivity.this,MainActivity.class).setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP));
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




}