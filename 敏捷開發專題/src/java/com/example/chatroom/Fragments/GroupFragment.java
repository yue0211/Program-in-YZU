package com.example.chatroom.Fragments;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.chatroom.Adapter.GroupAdapter;
import com.example.chatroom.Adapter.UserAdapter;
import com.example.chatroom.GroupActivity;
import com.example.chatroom.MessageActivity;
import com.example.chatroom.Model.Chatlist;
import com.example.chatroom.Model.Group;
import com.example.chatroom.Model.User;
import com.example.chatroom.R;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.bottomsheet.BottomSheetDialog;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

// 此為最初的Users

public class GroupFragment extends Fragment {

    private RecyclerView recyclerView;

    private GroupAdapter groupAdapter;
    private List<Group>mUsers=new ArrayList<>();
    private BottomSheetDialog bottomSheetDialog;

    EditText GroupName;
    DatabaseReference reference;
    private String TAG = GroupFragment.class.getSimpleName();

    EditText search_users;
    ImageButton btn_send;
    FloatingActionButton addgroup;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragment_group, container, false);

        recyclerView = view.findViewById(R.id.recycler_view);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(getContext()));
        addgroup = view.findViewById(R.id.addmessage);

        //readUsers();

        search_users = view.findViewById(R.id.search_users);

        btn_send = view.findViewById(R.id.btn_send);
        FirebaseUser fuser = FirebaseAuth.getInstance().getCurrentUser();
        reference = FirebaseDatabase.getInstance().getReference("Groups");

        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                chatList();
            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {}
        });
        reference.push();
        btn_send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {}

        });
        search_users.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                searchUsers(charSequence.toString().toLowerCase());
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });
        addgroup.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                showBottomSheetDialog();

            }
        });
        return view;
    }

    private void chatList() {

        FirebaseUser fuser = FirebaseAuth.getInstance().getCurrentUser();
        reference = FirebaseDatabase.getInstance().getReference("Groups");

        reference.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                mUsers.clear();
                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                {
                    for(DataSnapshot data : dataSnapshot.child("Users").getChildren()){
                        if(data.getValue().toString().equals(fuser.getUid())){
                            Group groupbuf=new Group();
                            groupbuf.setId(dataSnapshot.getKey());
                            groupbuf.setImageURL(dataSnapshot.child("pic").getValue().toString());
                            groupbuf.setUsername(dataSnapshot.child("Name").getValue().toString());
                            mUsers.add(groupbuf);
                        }
                    }
                }
                groupAdapter = new GroupAdapter(getContext(),mUsers);
                recyclerView.setAdapter(groupAdapter);
            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {}
        });
    }

    private void showBottomSheetDialog() {

        bottomSheetDialog = new BottomSheetDialog(this.getContext());
        bottomSheetDialog.setContentView(R.layout.bottom_sheet_dialog_group_layout);

        GroupName = bottomSheetDialog.findViewById(R.id.search_users);

        btn_send = bottomSheetDialog.findViewById(R.id.btn_send);


        btn_send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                String groupname=GroupName.getText().toString();
                if(TextUtils.isEmpty(groupname)){
                    Toast.makeText(getContext(),"名稱不得為空",Toast.LENGTH_SHORT).show();
                }else{
                    CreatNewGroup(groupname);
                }

            }

        });

        bottomSheetDialog.show();

    }

    private void CreatNewGroup(String groupname) {
        FirebaseUser fuser = FirebaseAuth.getInstance().getCurrentUser();
        HashMap<String,Object> hashMap = new HashMap<>();
        hashMap.put("Name", groupname);
        hashMap.put("Users", 0);
        hashMap.put("pic", "default");
        hashMap.put("oshi_name", "");
        hashMap.put("oshi_from", "");
        //hashMap.put("Chats", 0);
        reference = FirebaseDatabase.getInstance().getReference().child("Groups");
        DatabaseReference buff=reference;
        buff.push().setValue(hashMap);
        buff.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                String id="";
                if(snapshot.exists())
                {
                    for (DataSnapshot postSnapshot: snapshot.getChildren()) {
                        id=postSnapshot.getKey();
                    }
                }
                reference = FirebaseDatabase.getInstance().getReference().child("Groups").child(id).child("Users");
                String finalId = id;
                reference.push().setValue(fuser.getUid()).addOnCompleteListener(new OnCompleteListener<Void>() {
                    @Override
                    public void onComplete(@NonNull Task<Void> task) {
                        if(task.isSuccessful()){
                            Toast.makeText(getContext(),groupname+"已建立",Toast.LENGTH_SHORT).show();
                            Intent intent = new Intent(getContext(), GroupActivity.class);
                            intent.putExtra("userid", finalId);
                            getContext().startActivity(intent);
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
    private void searchUsers(String toString)
    {
        Query query = FirebaseDatabase.getInstance().getReference("Groups").orderByChild("Name")
                .startAt(toString)
                .endAt(toString+ "\uf8ff");

        query.addValueEventListener(new ValueEventListener() {

            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot)
            {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups");
                FirebaseUser fuser = FirebaseAuth.getInstance().getCurrentUser();
                if(mUsers != null)
                    mUsers.clear();
                Group user = new Group();
                for(DataSnapshot dataSnapshot: snapshot.getChildren())
                {
                    reference.child(dataSnapshot.getKey()).child("Users").addListenerForSingleValueEvent(new ValueEventListener() {
                        @Override
                        public void onDataChange(@NonNull DataSnapshot snapshot1) {
                            for(DataSnapshot snapshot2:snapshot1.getChildren()){
                                if(snapshot2.getValue().toString().equals(fuser.getUid())){
                                    user.setUsername(dataSnapshot.child("Name").getValue().toString());
                                    user.setImageURL(dataSnapshot.child("pic").getValue().toString());
                                    user.setId(dataSnapshot.getKey().toString());
                                    mUsers.add(user);
                                }
                            }
                        }

                        @Override
                        public void onCancelled(@NonNull DatabaseError error) {}
                    });

                    assert user != null;
                    assert fuser != null;
                }

                if(toString.length()==0){
                    chatList();
                }
                else
                {
                    groupAdapter = new GroupAdapter(getContext(),mUsers);
                    recyclerView.setAdapter(groupAdapter);
                }}

            @Override
            public void onCancelled(@NonNull DatabaseError error)
            {            }
        });
    }
}