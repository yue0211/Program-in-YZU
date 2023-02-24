package com.example.chatroom.Adapter;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.example.chatroom.GroupActivity;
import com.example.chatroom.GroupProfileActivity;
import com.example.chatroom.MessageActivity;
import com.example.chatroom.Model.Chat;
import com.example.chatroom.Model.Group;
import com.example.chatroom.Model.User;
import com.example.chatroom.OtherProfileActivity;
import com.example.chatroom.R;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.List;

public class GroupAdapter extends RecyclerView.Adapter<GroupAdapter.ViewHolder>{


    private static final String TAG = "韭菜";
    private Context mContext;
    private List<Group> mUsers;

    String theLastMessage;

    public GroupAdapter(Context mContext, List<Group> mUsers)
    {
        this.mContext = mContext;
        this.mUsers = mUsers;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(mContext).inflate(R.layout.group_item,parent,false);
        Log.e(TAG, "onCreateViewHolder: 韭菜猴");
        return new GroupAdapter.ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        final Group user = mUsers.get(position);
        holder.username.setText(user.getUsername());

        if(user.getImageURL().equals("default"))
            holder.profile_image.setImageResource(R.mipmap.ic_launcher);
        else
            Glide.with(mContext).load(user.getImageURL()).into(holder.profile_image);


        lastMessage(user.getId(),holder.last_msg);

        holder.profile_image.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(mContext, GroupProfileActivity.class);
                intent.putExtra("userid",user.getId());
                mContext.startActivity(intent);
            }
        });

        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(mContext, GroupActivity.class);
                intent.putExtra("userid",user.getId());
                mContext.startActivity(intent);
            }
        });
    }

    @Override
    public int getItemCount() {
        return mUsers.size();
    }


    public class ViewHolder extends RecyclerView.ViewHolder{

        public TextView username;
        public ImageView profile_image;
        private TextView last_msg;



        public ViewHolder(@NonNull View itemView) {
            super(itemView);

            username = itemView.findViewById(R.id.username);
            profile_image = itemView.findViewById(R.id.profile_image);
            last_msg = itemView.findViewById(R.id.last_msg);
        }


    }


    private void lastMessage(final String userid, TextView last_msg)
    {
        theLastMessage = "default";

        FirebaseUser firebaseUser = FirebaseAuth.getInstance().getCurrentUser();
        if(firebaseUser == null)
            return;
        DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(userid).child("Chats");

        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                for(DataSnapshot dataSnapshot : snapshot.getChildren())
                {
                    Chat chat = dataSnapshot.getValue(Chat.class);

                    if(firebaseUser.getUid()!=null) {
                        if (!chat.getMessage().equals("") && !chat.getUserCantSee().contains(FirebaseAuth.getInstance().getCurrentUser().getUid()))
                            if(chat.getType().equals("text"))
                                theLastMessage = chat.getMessage();
                            else
                                theLastMessage="傳送了一張圖片";
                        if (chat.getMessage().equals(""))
                            theLastMessage = "這則訊息已被收回";
                    }
                }


                switch (theLastMessage)
                {
                    case "default":
                        last_msg.setText("沒有訊息");
                        break;


                    default:
                        last_msg.setText(theLastMessage);
                        break;
                }

                theLastMessage = "default";

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });


    }


}
