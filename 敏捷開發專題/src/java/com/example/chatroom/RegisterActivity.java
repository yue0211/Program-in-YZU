package com.example.chatroom;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.textfield.TextInputEditText;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.SignInMethodQueryResult;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;
import java.util.Locale;

import com.example.chatroom.MessageActivity.*;

public class RegisterActivity extends AppCompatActivity {

    TextInputEditText username,email,password;
    Button btn_register;

    FirebaseAuth auth;
    DatabaseReference reference;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);



        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setTitle("Register");
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        username = findViewById(R.id.username);
        email = findViewById(R.id.email);
        password = findViewById(R.id.password);
        btn_register = findViewById(R.id.btn_register);

        auth = FirebaseAuth.getInstance();


        btn_register.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view)
            {
                String txt_username = username.getText().toString();
                String txt_email = email.getText().toString();
                String txt_password = password.getText().toString();

                if(TextUtils.isEmpty(txt_username)||TextUtils.isEmpty(txt_email)||TextUtils.isEmpty(txt_password))
                    Toast.makeText(RegisterActivity.this,"每個欄位都需要填寫",Toast.LENGTH_SHORT).show();
                else if(txt_password.length() < 6 )
                    Toast.makeText(RegisterActivity.this,"密碼最少要是六位數",Toast.LENGTH_SHORT).show();
                else
                    register(txt_username,txt_email,txt_password);

            }

        });




    }

    private void register(String username,String email,String password){

        auth.createUserWithEmailAndPassword(email,password)
                .addOnCompleteListener(new OnCompleteListener<AuthResult>()
                {

                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task)
                    {
                        if(task.isSuccessful())
                        {
                            FirebaseUser firebaseUser = auth.getCurrentUser();
                            assert firebaseUser != null;
                            firebaseUser.sendEmailVerification();
                            String userid = firebaseUser.getUid();
                            String email = firebaseUser.getEmail();
                            reference = FirebaseDatabase.getInstance().getReference(getString(R.string.S)).child(userid);

                            HashMap<String,String>hashMap = new HashMap<>();
                            hashMap.put("id",userid);
                            hashMap.put("username",username);
                            hashMap.put("imageURL","default");
                            hashMap.put("status","offline");
                            hashMap.put("email",email);
                            hashMap.put("search",username.toLowerCase());
                            hashMap.put("oshi_name","");
                            hashMap.put("oshi_from","");
                            hashMap.put("oshi_reason","");
                            hashMap.put("oshi_imageURL","default");

                            reference.setValue(hashMap).addOnCompleteListener(new OnCompleteListener<Void>() {
                                @Override
                                public void onComplete(@NonNull Task<Void> task)
                                {
                                    if(task.isSuccessful())
                                    {
                                        Intent intent = new Intent(RegisterActivity.this,MainActivity.class);
                                        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK|Intent.FLAG_ACTIVITY_NEW_TASK);
                                        Toast.makeText(RegisterActivity.this,"請去信箱確認您的認證信",Toast.LENGTH_LONG).show();
                                        startActivity(intent);
                                        finish();

                                        new MessageActivity().rbtMessInit(auth.getCurrentUser().getUid(), "0");

                                    }

                                }
                            });


                        }
                        else
                            Toast.makeText(RegisterActivity.this,"你無法使用此email或密碼註冊",Toast.LENGTH_SHORT).show();





                    }
                });


    }








}