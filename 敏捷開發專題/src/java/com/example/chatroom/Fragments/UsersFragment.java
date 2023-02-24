package com.example.chatroom.Fragments;

import android.content.Context;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.example.chatroom.Adapter.UserAdapter;
import com.example.chatroom.MessageActivity;
import com.example.chatroom.Model.Chat;
import com.example.chatroom.Model.Chatlist;
import com.example.chatroom.Model.User;
import com.example.chatroom.Notifications.Token;
import com.example.chatroom.R;
import com.google.android.gms.common.internal.safeparcel.SafeParcelable;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.bottomsheet.BottomSheetBehavior;
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
import com.google.firebase.iid.internal.FirebaseInstanceIdInternal;
import com.google.firebase.messaging.FirebaseMessaging;
import com.google.firebase.messaging.FirebaseMessagingService;

import java.util.ArrayList;
import java.util.List;
// 此為最初的Chats




public class UsersFragment extends Fragment {

    private RecyclerView recyclerView2;

    private UserAdapter userAdapter2;
    private List<User>mUsers2;

    EditText search_users2;
    ImageButton btn_send;
    private BottomSheetDialog bottomSheetDialog;

    ////////////////////////////////上面是原本的chatFragment的設定
    private RecyclerView recyclerView;

    private UserAdapter userAdapter;

    private List<User> mUsers;

    FirebaseUser fuser;
    DatabaseReference reference;

    private List<Chatlist> usersList;

    private String TAG = UsersFragment.class.getSimpleName();

    private User privateuser;

    EditText search_users;

    FloatingActionButton addmessage;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragment_users, container, false);

        recyclerView = view.findViewById(R.id.recycler_view);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(getContext()));

        search_users = view.findViewById(R.id.search_users);

        addmessage = view.findViewById(R.id.addmessage);

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


        fuser = FirebaseAuth.getInstance().getCurrentUser();

        usersList = new ArrayList<>();

        reference = FirebaseDatabase.getInstance().getReference("Chatlist").child(fuser.getUid());

        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                usersList.clear();

                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                {
                    Chatlist chatlist = dataSnapshot.getValue(Chatlist.class);
                    usersList.add(chatlist);
                }

                chatList();


            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });


        FirebaseMessaging.getInstance().getToken().addOnCompleteListener(new OnCompleteListener<String>() {

            @Override
            public void onComplete(@NonNull Task<String> task)
            {
                String token = task.getResult();

                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Tokens");
                Token token1 = new Token(token);
                reference.child(fuser.getUid()).setValue(token1);
            }

        });

        addmessage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                showBottomSheetDialog();

            }
        });



        return view;
    }

    private void showBottomSheetDialog() {

        bottomSheetDialog = new BottomSheetDialog(this.getContext());
        bottomSheetDialog.setContentView(R.layout.bottom_sheet_dialog_layout);


        recyclerView2 = bottomSheetDialog.findViewById(R.id.recycler_view);
        recyclerView2.setHasFixedSize(true);
        recyclerView2.setLayoutManager(new LinearLayoutManager(getContext()));

        mUsers2 = new ArrayList<>();

        //readUsers();

        search_users2 = bottomSheetDialog.findViewById(R.id.search_users);

        btn_send = bottomSheetDialog.findViewById(R.id.btn_send);


        btn_send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                FirebaseUser fuser = FirebaseAuth.getInstance().getCurrentUser();
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Users");

                DatabaseReference userference = FirebaseDatabase.getInstance().getReference("Users").child(fuser.getUid());
                userference.get().addOnCompleteListener(new OnCompleteListener<DataSnapshot>() {
                    @Override
                    public void onComplete(@NonNull Task<DataSnapshot> task) {
                        privateuser = task.getResult().getValue(User.class);
                        Log.e(TAG,"privateUSer");
                    }
                });


                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {

                        List<User> usersList = new ArrayList<>();
                        usersList.clear();
                        mUsers2.clear();
                        for(DataSnapshot dataSnapshot : snapshot.getChildren())
                        {
                            User user = dataSnapshot.getValue(User.class);
                            usersList.add(user);
                        }

                        for (int i = 0; i < usersList.size(); i++)
                        {
                            String temp = usersList.get(i).getEmail();

                            if (privateuser!=null&&search_users2.getText().toString().equals(fuser.getEmail())) {
                                Toast.makeText(getContext(),"無法查詢本身帳號",Toast.LENGTH_SHORT).show();
                                break;
                            }
                            else if (search_users2.getText().toString().equals(temp))
                            {
                                Log.e(TAG, "機掰");
                                mUsers2.add(usersList.get(i));
                                userAdapter = new UserAdapter(getContext(),mUsers2,false);
                                recyclerView2.setAdapter(userAdapter);


                                if(privateuser!=null)
                                {
                                    InputMethodManager imm = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
                                    imm.hideSoftInputFromWindow(search_users2.getWindowToken(),0);
                                }

                                break;
                            }
                           /* else if (search_users.getText().toString().equals("chartrobot001@gmail.com")) {
                                Toast.makeText(getContext(),"無法查詢機器人帳號",Toast.LENGTH_SHORT).show();
                                break;
                            }*/

                            if((privateuser!=null)&&(getContext()!=null)&&(i==(usersList.size()-1)))
                                Toast.makeText(getContext(),"使用此帳號的使用者不存在 請重新輸入",Toast.LENGTH_SHORT).show();

                        }

                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {

                    }
                });

            }

        });

        bottomSheetDialog.show();

    }

    @Override
    public void onPause() {
        super.onPause();
        if(bottomSheetDialog!=null)
        {
            bottomSheetDialog.dismiss();
            privateuser = null;
        }

    }




    private void chatList()
    {

        mUsers = new ArrayList<>();
        reference = FirebaseDatabase.getInstance().getReference("Users");

        reference.addValueEventListener(new ValueEventListener() {

            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                mUsers.clear();

                for(DataSnapshot dataSnapshot:snapshot.getChildren())
                {
                    User user = dataSnapshot.getValue(User.class);

                    for(Chatlist chatlist:usersList)
                        if(user.getId() != null)
                            if(user.getId().equals(chatlist.getId()))
                                mUsers.add(user);

                }

                userAdapter = new UserAdapter(getContext(),mUsers,true);
                recyclerView.setAdapter(userAdapter);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

    }




    private void searchUsers(String toString)
    {

        DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Chatlist");
        FirebaseUser fuser = FirebaseAuth.getInstance().getCurrentUser();

        List<Chatlist> chatlist = new ArrayList<>();
        chatlist.clear();

        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

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
                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        Query query = FirebaseDatabase.getInstance().getReference("Users").orderByChild("search")
                .startAt(toString)
                .endAt(toString+ "\uf8ff");

        query.addValueEventListener(new ValueEventListener() {

            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot)
            {
                if(mUsers != null)
                    mUsers.clear();
                for(DataSnapshot dataSnapshot: snapshot.getChildren())
                {
                    User user = dataSnapshot.getValue(User.class);

                    assert user != null;
                    assert fuser != null;

                    for(int i=0;i<chatlist.size();i++)
                        if(user.getId().equals(chatlist.get(i).getId()))
                            mUsers.add(user);

                }

                if(toString.length()==0)
                    chatList();
                else
                {
                    userAdapter = new UserAdapter(getContext(),mUsers,true);
                    recyclerView.setAdapter(userAdapter);
                }


            }

            @Override
            public void onCancelled(@NonNull DatabaseError error)
            {

            }
        });





    }
}