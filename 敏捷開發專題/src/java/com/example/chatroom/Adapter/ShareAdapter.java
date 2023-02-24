package com.example.chatroom.Adapter;

import android.content.Context;
import android.util.Log;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.example.chatroom.MessageActivity;
import com.example.chatroom.Model.Chat;
import com.example.chatroom.Model.User;
import com.example.chatroom.Notifications.Data;
import com.example.chatroom.Notifications.MyResponse;
import com.example.chatroom.Notifications.Sender;
import com.example.chatroom.Notifications.Token;
import com.example.chatroom.R;
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
import java.util.HashMap;
import java.util.List;


public class ShareAdapter extends RecyclerView.Adapter<ShareAdapter.ViewHolder>{


    private Context mContext;
    private List<User> mUsers;
    private String currentUserId;


    public static Chat chat;
    private FirebaseUser fuser;

    public ShareAdapter(Context mContext, List<User> mUsers, String currentUserId)
    {
        this.mContext = mContext;
        this.mUsers = mUsers;
        this.currentUserId = currentUserId;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(mContext).inflate(R.layout.user_item,parent,false);
        return new ShareAdapter.ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        final User user = mUsers.get(position);
        holder.username.setText(user.getUsername());

        if(user.getImageURL().equals("default"))
            holder.profile_image.setImageResource(R.mipmap.ic_launcher);
        else
            Glide.with(mContext).load(user.getImageURL()).into(holder.profile_image);

        holder.send_mess.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                sendMessage(currentUserId, user.getId(), mContext);

                String sender = currentUserId, receiver = user.getId();

                DatabaseReference reference = FirebaseDatabase.getInstance().getReference();

                Pair<String, String> TimePair = getTime( 8 );
                String Date = TimePair.first;
                String Time = TimePair.second;

                HashMap<String,Object> hashMap = new HashMap<>();
                hashMap.put("sender", sender);
                hashMap.put("receiver", receiver);
                hashMap.put("message", chat.getMessage());
                hashMap.put("isseen",false);
                hashMap.put("date",Date);
                hashMap.put("Time",Time);
                hashMap.put("type",chat.getType());

                hashMap.put("userCantSee","");

                hashMap.put("emoji_smile","");
                hashMap.put("emoji_love","");
                hashMap.put("emoji_cry","");
                hashMap.put("emoji_angry","");
                hashMap.put("emoji_nothing","");
                hashMap.put("emoji_good","");
                if(user.getEmail().equals("")){
                    reference.child("Groups").child(user.getId()).child("Chats").push().setValue(hashMap);
                }
                else{
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
                }

                final String msg = chat.getMessage();


                fuser = FirebaseAuth.getInstance().getCurrentUser();


                if(fuser != null)
                    reference = FirebaseDatabase.getInstance().getReference("Users").child(fuser.getUid());
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        User Fuser = snapshot.getValue(User.class);
                        if(user.getEmail().equals("")){
                            sendNotification(receiver,"",msg);
                        }else{
                            sendNotification(receiver,Fuser.getUsername(),msg);
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {

                    }
                });


                holder.send_mess.setText("已傳送");
                holder.send_mess.setEnabled(false);

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



    private void sendNotification(String receiver,String username, String message)
    {
        DatabaseReference tokens = FirebaseDatabase.getInstance().getReference("Tokens");
        if(username.equals("")){
            DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(receiver).child("Users");
            reference.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    for (DataSnapshot dataSnapshot:snapshot.getChildren()){
                        Query query = tokens.orderByKey().equalTo(dataSnapshot.getValue().toString());

                        query.addValueEventListener(new ValueEventListener() {
                            @Override
                            public void onDataChange(@NonNull DataSnapshot snapshot) {

                                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                                {
                                    Token token = dataSnapshot.getValue(Token.class);
                                    Data data = new Data(fuser.getUid(),R.mipmap.ic_launcher,username+": "+message,"新訊息",currentUserId);

                                    Sender sender = new Sender(data,token.getToken());
                                }
                            }

                            @Override
                            public void onCancelled(@NonNull DatabaseError error) {
                            }
                        });
                    }
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {

                }
            });
        }else {
            Query query = tokens.orderByKey().equalTo(receiver);

            query.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {

                    for(DataSnapshot dataSnapshot : snapshot.getChildren())
                    {
                        Token token = dataSnapshot.getValue(Token.class);
                        Data data = new Data(fuser.getUid(),R.mipmap.ic_launcher,username+": "+message,"新訊息",currentUserId);

                        Sender sender = new Sender(data,token.getToken());
                    }
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {
                }
            });
        }
    }


    @Override
    public int getItemCount() {
        return mUsers.size();
    }


    public class ViewHolder extends RecyclerView.ViewHolder{

        public TextView username;
        public ImageView profile_image;
        public Button send_mess;




        public ViewHolder(@NonNull View itemView) {
            super(itemView);

            username = itemView.findViewById(R.id.username);
            profile_image = itemView.findViewById(R.id.profile_image);
            send_mess = itemView.findViewById(R.id.send_mess);

            send_mess.setVisibility(View.VISIBLE);

        }


    }




}
