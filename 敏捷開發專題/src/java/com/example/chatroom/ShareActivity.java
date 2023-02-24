package com.example.chatroom;

import android.os.Bundle;

import com.example.chatroom.Adapter.ShareAdapter;
import com.example.chatroom.Adapter.UserAdapter;
import com.example.chatroom.Fragments.UsersFragment;
import com.example.chatroom.Model.Chat;
import com.example.chatroom.Model.Chatlist;
import com.example.chatroom.Model.User;
import com.google.android.material.appbar.CollapsingToolbarLayout;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.util.Log;
import android.view.View;

import com.example.chatroom.databinding.ActivityShareBinding;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.List;

public class ShareActivity extends AppCompatActivity {

    private ActivityShareBinding binding;

    private RecyclerView recyclerView;

    private List<User> mUsers;
    private DatabaseReference reference;
    private FirebaseUser fuser;
    private List<Chatlist> chatlist = new ArrayList<>();
    private ShareAdapter shareAdapter;

    private String TAG = ShareActivity.class.getSimpleName();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);



        binding = ActivityShareBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Toolbar toolbar = binding.toolbar;
        setSupportActionBar(toolbar);
        CollapsingToolbarLayout toolBarLayout = binding.toolbarLayout;
        toolBarLayout.setTitle("分享訊息");


        recyclerView = findViewById(R.id.recycler_view);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(getApplicationContext()));


        reference = FirebaseDatabase.getInstance().getReference("Chatlist");
        fuser = FirebaseAuth.getInstance().getCurrentUser();


        chatlist.clear();

        reference.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                Log.e(TAG,"近來第二次"+chatlist.size());

                //

                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                {
                    String temp = dataSnapshot.getKey().toString();


                    if(temp.equals(fuser.getUid()))
                    {

                        for(DataSnapshot dataSnapshot2 : dataSnapshot.getChildren())
                        {

                            Chatlist chat = dataSnapshot2.getValue(Chatlist.class);
                            chatlist.add(chat);
                        }

                        Log.e(TAG,"近來第一次"+chatlist.size());
                    }
                }


                DatabaseReference reference2 = FirebaseDatabase.getInstance().getReference("Users");
                reference2.addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {



                        if(mUsers != null)
                            mUsers.clear();

                        mUsers = new ArrayList<>();

                        for(DataSnapshot dataSnapshot: snapshot.getChildren())
                        {
                            User user = dataSnapshot.getValue(User.class);

                            assert user != null;
                            assert fuser != null;

                            for(int i = 0; i < chatlist.size(); i++)
                                if(user.getId().equals(chatlist.get(i).getId()))
                                    if(!user.getId().equals(fuser.getUid()))
                                        mUsers.add(user);

                        }


                        Log.e(TAG,"沒有能力"+mUsers.size());
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {

                    }
                });
                DatabaseReference reference3 = FirebaseDatabase.getInstance().getReference("Groups");


                reference3.addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        for (DataSnapshot dataSnapshot: snapshot.getChildren()){
                            for(DataSnapshot dataSnapshot1: dataSnapshot.child("Users").getChildren()){
                                if(dataSnapshot1.getValue().toString().equals(fuser.getUid())){
                                    User user = new User();
                                    user.setId(dataSnapshot.getKey());
                                    user.setUsername(dataSnapshot.child("Name").getValue().toString());
                                    user.setImageURL(dataSnapshot.child("pic").getValue().toString());
                                    user.setEmail("");
                                    mUsers.add(user);
                                }
                            }
                        }
                        Log.e(TAG,"Kokodayo"+mUsers.size());
                        shareAdapter = new ShareAdapter(getApplicationContext(), mUsers , fuser.getUid());
                        recyclerView.setAdapter(shareAdapter);
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {

                    }
                });

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }}