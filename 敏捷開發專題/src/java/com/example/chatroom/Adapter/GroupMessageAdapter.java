package com.example.chatroom.Adapter;

import static android.content.Context.CLIPBOARD_SERVICE;

import android.annotation.SuppressLint;
import android.app.DownloadManager;
import android.app.ProgressDialog;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Environment;
import android.text.InputType;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.amrdeveloper.reactbutton.ReactButton;
import com.amrdeveloper.reactbuttonlibrary.ReactionButton;
import com.bumptech.glide.Glide;
import com.example.chatroom.GroupActivity;
//import com.example.chatroom.MessageActivity;
import com.example.chatroom.Model.Chat;
import com.example.chatroom.R;
import com.example.chatroom.ShareActivity;
import com.example.chatroom.Show_Full_Image;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.squareup.picasso.Picasso;

import java.io.File;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Objects;


public class GroupMessageAdapter extends RecyclerView.Adapter<GroupMessageAdapter.ViewHolder> {

    public static final int MSG_TYPE_LEFT = 0;
    public static final int MSG_TYPE_RIGHT = 1;
    public static int holderPosition = -1;
    public static int longViewH = 0;

    private Context mContext;
    private List<Chat> mChat;
    private String groupid;
    private ProgressDialog mProgressDialog;

    FirebaseUser fuser;

    private String TAG = GroupMessageAdapter.class.getSimpleName();


    private int check = 0;


    public GroupMessageAdapter(Context mContext, List<Chat> mChat,String groupid) {
        this.mContext = mContext;
        this.mChat = mChat;
        this.groupid=groupid;
    }

    @NonNull
    @Override
    public GroupMessageAdapter.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {

        if (viewType == MSG_TYPE_RIGHT) {
            View view = LayoutInflater.from(mContext).inflate(R.layout.chat_item_right, parent, false);
            return new GroupMessageAdapter.ViewHolder(view);
        } else {
            View view = LayoutInflater.from(mContext).inflate(R.layout.chat_item_left, parent, false);
            return new GroupMessageAdapter.ViewHolder(view);
        }
    }

    private class DownloadImage extends AsyncTask<String, Integer, Bitmap> {
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            mProgressDialog = new ProgressDialog(mContext);
            mProgressDialog.setTitle("Download Image Tutorial");
            mProgressDialog.setMessage("Loading...");
            mProgressDialog.setIndeterminate(false);
            mProgressDialog.show();
        }

        @Override
        protected Bitmap doInBackground(String... URL) {
            String imageURL = URL[0];
            try {
                DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyMMddHHmmss");
                downloadImageNew(dtf.format(LocalDateTime.now()), imageURL);
            } catch (Exception e) {
                e.printStackTrace();
            }
            return null;
        }

        @Override
        protected void onPostExecute(Bitmap result) {
            // Close progressdialog
            mProgressDialog.dismiss();
        }
    }

    private void downloadImageNew(String filename, String downloadUrlOfImage) {
        try {

            DownloadManager dm = (DownloadManager) mContext.getSystemService(Context.DOWNLOAD_SERVICE);
            Uri downloadUri = Uri.parse(downloadUrlOfImage);
            DownloadManager.Request request = new DownloadManager.Request(downloadUri);
            request.setAllowedNetworkTypes(DownloadManager.Request.NETWORK_WIFI | DownloadManager.Request.NETWORK_MOBILE)
                    .setAllowedOverRoaming(false)
                    .setTitle(filename)
                    .setMimeType("image/jpeg") // Your file type. You can use this code to download other file types also.
                    .setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED)
                    .setDestinationInExternalPublicDir(Environment.DIRECTORY_PICTURES, File.separator + filename + ".jpg");
            dm.enqueue(request);
            Toast.makeText(mContext, "圖片開始下載", Toast.LENGTH_SHORT).show();
        } catch (Exception e) {
            Toast.makeText(mContext, "圖片下載失敗", Toast.LENGTH_SHORT).show();
        }
    }

    public int dpToPx(int dp) {
        return (int) (dp * Resources.getSystem().getDisplayMetrics().density);
    }

    public int spToPx(int sp) {
        return (int) (sp * Resources.getSystem().getDisplayMetrics().scaledDensity);
    }

    public void showEmoji(@NonNull ViewHolder holder, @NonNull Chat chat) {
        String emoji_smile = chat.getEmoji_smile().replaceAll(" ", "");
        String emoji_love = chat.getEmoji_love().replaceAll(" ", "");
        String emoji_cry = chat.getEmoji_cry().replaceAll(" ", "");
        String emoji_angry = chat.getEmoji_angry().replaceAll(" ", "");
        String emoji_nothing = chat.getEmoji_nothing().replaceAll(" ", "");
        String emoji_good = chat.getEmoji_good().replaceAll(" ", "");


        if (!emoji_smile.equals(""))
            holder.emoji_smile.setVisibility(View.VISIBLE);
        else
            holder.emoji_smile.setVisibility(View.GONE);

        if (!emoji_love.equals(""))
            holder.emoji_love.setVisibility(View.VISIBLE);
        else
            holder.emoji_love.setVisibility(View.GONE);

        if (!emoji_cry.equals(""))
            holder.emoji_cry.setVisibility(View.VISIBLE);
        else
            holder.emoji_cry.setVisibility(View.GONE);

        if (!emoji_angry.equals(""))
            holder.emoji_angry.setVisibility(View.VISIBLE);
        else
            holder.emoji_angry.setVisibility(View.GONE);

        if (!emoji_nothing.equals(""))
            holder.emoji_nothing.setVisibility(View.VISIBLE);
        else
            holder.emoji_nothing.setVisibility(View.GONE);

        if (!emoji_good.equals(""))
            holder.emoji_good.setVisibility(View.VISIBLE);
        else
            holder.emoji_good.setVisibility(View.GONE);

        int react_number_int = -6;

        react_number_int += chat.getEmoji_smile().split("\\s+").length;
        react_number_int += chat.getEmoji_love().split("\\s+").length;
        react_number_int += chat.getEmoji_cry().split("\\s+").length;
        react_number_int += chat.getEmoji_angry().split("\\s+").length;
        react_number_int += chat.getEmoji_nothing().split("\\s+").length;
        react_number_int += chat.getEmoji_good().split("\\s+").length;

        holder.react_number.setText(Integer.toString(react_number_int));
        if (Integer.parseInt((String) holder.react_number.getText()) == 0)
            holder.react_number.setVisibility(View.GONE);
        else
            holder.react_number.setVisibility(View.VISIBLE);


    }


    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, @SuppressLint("RecyclerView") int position) {

        Chat chat = mChat.get(position);
        DatabaseReference reference4 = FirebaseDatabase.getInstance().getReference("Users").child(chat.getSender());

        reference4.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                holder.username.setText(snapshot.child("username").getValue().toString());
                String imageurl=snapshot.child("imageURL").getValue().toString();
                if (imageurl.equals("default"))
                    holder.profile_image.setImageResource(R.mipmap.ic_launcher);
                else
                    Glide.with(mContext).load(imageurl).into(holder.profile_image);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        holder.show_message.setText(chat.getMessage());
        if (chat.getType().equals("text"))
        {
            if (chat.getMessage().equals("這則訊息已被收回")) {
                holder.show_message.setBackgroundColor(Color.argb(0, 0, 0, 0));
                holder.show_message.setTextColor(Color.argb(150, 100, 100, 100));
                holder.send_date.setTextColor(Color.argb(150, 100, 100, 100));
                holder.send_time.setTextColor(Color.argb(150, 100, 100, 100));
                holder.txt_seen.setVisibility(View.GONE);
            }
            else {
                holder.show_message.setBackgroundColor(Color.parseColor("#FF3F51B5"));
                holder.show_message.setTextColor(Color.parseColor("#ffffff"));
                holder.send_date.setTextColor(Color.parseColor("#757575"));
                holder.send_time.setTextColor(Color.parseColor("#757575"));

                String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();

                if (chat.getSender().equals(currentUserId))  //right
                    holder.show_message.setBackgroundResource(R.drawable.background_right);
                else
                    holder.show_message.setBackgroundResource(R.drawable.background_left);


                RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
                int dp_to_px_5 = dpToPx(5), dp_to_px_8 = dpToPx(8);

                if (chat.getSender().equals(currentUserId)) {// right
                    params.addRule(RelativeLayout.ALIGN_PARENT_END);
                    params.setMargins(0, 0, 0, 0);
                } else {
                    params.addRule(RelativeLayout.RIGHT_OF, R.id.profile_image);
                    params.setMargins(dp_to_px_5, 0, 0, 0);
                }

                holder.show_message.setLayoutParams(params);
                holder.show_message.setInputType(InputType.TYPE_CLASS_TEXT |
                        InputType.TYPE_TEXT_FLAG_MULTI_LINE |
                        InputType.TYPE_TEXT_FLAG_CAP_SENTENCES);

                holder.show_message.setMaxWidth(dpToPx(175));
                holder.show_message.setMaxLines(999999999);
                holder.show_message.setPadding(dp_to_px_8, dp_to_px_8, dp_to_px_8, dp_to_px_8);
                holder.show_message.setTextSize(18);

            }
            holder.show_message.setOnLongClickListener(new View.OnLongClickListener() {
                @Override
                public boolean onLongClick(View view) {
                    if (chat.getMessage().equals("這則訊息已被收回")) return true;

                    GroupActivity.MessagegClear();
                    GroupActivity.EmojiClear();
                    holder.download.setVisibility(View.GONE);
                    holder.choice.setVisibility(View.VISIBLE);
                    holder.top.setVisibility(View.VISIBLE);
                    return true;
                }
            });
        }
        else {
            if (chat.getMessage().equals("這則訊息已被收回"))
            {
                holder.show_message.setBackgroundColor(Color.argb(0, 0, 0, 0));
                holder.show_message.setTextColor(Color.argb(150, 100, 100, 100));
                holder.send_date.setTextColor(Color.argb(150, 100, 100, 100));
                holder.send_time.setTextColor(Color.argb(150, 100, 100, 100));
                holder.txt_seen.setVisibility(View.GONE);
            }
            else
            {
                String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                if (chat.getType().equals("iv")) {
                    Log.e(TAG, chat.getType());
                    RelativeLayout.LayoutParams params1 = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
                    params1.addRule(RelativeLayout.BELOW, R.id.send_Image);
                    if (chat.getSender().equals(currentUserId)) // right image
                        params1.addRule(RelativeLayout.LEFT_OF, R.id.send_Image);
                    else
                        params1.addRule(RelativeLayout.RIGHT_OF, R.id.send_Image);
                    params1.setMargins(0, -120, 0, 0);
                    holder.send_date.setLayoutParams(params1);
                    RelativeLayout.LayoutParams params2 = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
                    params2.addRule(RelativeLayout.BELOW, R.id.send_date);
                    if (chat.getSender().equals(currentUserId)) // right image
                        params2.addRule(RelativeLayout.LEFT_OF, R.id.send_Image);
                    else
                        params2.addRule(RelativeLayout.RIGHT_OF, R.id.send_Image);
                    holder.send_time.setLayoutParams(params2);
                    RelativeLayout.LayoutParams params3 = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
                    params3.addRule(RelativeLayout.BELOW, R.id.send_date);
                    if (chat.getSender().equals(currentUserId)) // right image
                        params3.addRule(RelativeLayout.LEFT_OF, R.id.send_date);
                    else
                        holder.txt_seen.setVisibility(View.GONE);
                    holder.txt_seen.setLayoutParams(params3);
                    RelativeLayout.LayoutParams params4 = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
                    params4.addRule(RelativeLayout.BELOW, R.id.send_Image);
                    if (chat.getSender().equals(currentUserId)) // right image
                    {
                        params4.addRule(RelativeLayout.RIGHT_OF, R.id.send_date);
                        params4.setMargins(20, 0, 0, 0);
                    } else
                        params4.addRule(RelativeLayout.LEFT_OF, R.id.send_date);
                    holder.emoji.setLayoutParams(params4);

                    holder.copy.setVisibility(View.GONE);
                }
                holder.show_message.setVisibility(View.GONE);
                holder.show_image.setVisibility(View.VISIBLE);



                Picasso.get().load(chat.getMessage()).into(holder.show_image);

                holder.show_image.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        // 按下Button要做的事

                        GroupActivity.MessagegClear();
                        GroupActivity.EmojiClear();

                        Intent intent;
                        intent = new Intent(view.getContext(), Show_Full_Image.class);
                        intent.putExtra("u", chat.getMessage());
                        mContext.startActivity(intent);
                    }

                });
                holder.show_image.setOnLongClickListener(new View.OnLongClickListener() {
                    @Override
                    public boolean onLongClick(View v) {

                        GroupActivity.MessagegClear();
                        GroupActivity.EmojiClear();
                        holder.choice.setVisibility(View.VISIBLE);
                        holder.top.setVisibility(View.VISIBLE);

                        return true;
                    }
                });
            }
        }

        String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();


        if (chat.getEmoji_smile().contains(currentUserId))
            holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_gray);
        if (chat.getEmoji_love().contains(currentUserId))
            holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_gray);
        if (chat.getEmoji_cry().contains(currentUserId))
            holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_gray);
        if (chat.getEmoji_angry().contains(currentUserId))
            holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_gray);
        if (chat.getEmoji_nothing().contains(currentUserId))
            holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_gray);
        if (chat.getEmoji_good().contains(currentUserId))
            holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_gray);


        showEmoji(holder, chat);

        int react_number_int = -6;

        react_number_int += chat.getEmoji_smile().split("\\s+").length;
        react_number_int += chat.getEmoji_love().split("\\s+").length;
        react_number_int += chat.getEmoji_cry().split("\\s+").length;
        react_number_int += chat.getEmoji_angry().split("\\s+").length;
        react_number_int += chat.getEmoji_nothing().split("\\s+").length;
        react_number_int += chat.getEmoji_good().split("\\s+").length;

        holder.react_number.setText(Integer.toString(react_number_int));
        if (Integer.parseInt((String) holder.react_number.getText()) == 0)
            holder.react_number.setVisibility(View.GONE);
        else
            holder.react_number.setVisibility(View.VISIBLE);


        Log.e(TAG, "creat holder " + holder.show_message.getText());
        DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                List<Chat> chatlist = new ArrayList<>();
                for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                    Chat chat = dataSnapshot.getValue(Chat.class);
                    assert chat != null;
                    if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                        String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();


                        if (chat.getEmoji_smile().contains(currentUserId))
                            holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_gray);
                        if (chat.getEmoji_love().contains(currentUserId))
                            holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_gray);
                        if (chat.getEmoji_cry().contains(currentUserId))
                            holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_gray);
                        if (chat.getEmoji_angry().contains(currentUserId))
                            holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_gray);
                        if (chat.getEmoji_nothing().contains(currentUserId))
                            holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_gray);
                        if (chat.getEmoji_good().contains(currentUserId))
                            holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_gray);


                        showEmoji(holder, chat);

                        int react_number_int2 = -6;

                        react_number_int2 += chat.getEmoji_smile().split("\\s+").length;
                        react_number_int2 += chat.getEmoji_love().split("\\s+").length;
                        react_number_int2 += chat.getEmoji_cry().split("\\s+").length;
                        react_number_int2 += chat.getEmoji_angry().split("\\s+").length;
                        react_number_int2 += chat.getEmoji_nothing().split("\\s+").length;
                        react_number_int2 += chat.getEmoji_good().split("\\s+").length;

                        holder.react_number.setText(Integer.toString(react_number_int2));
                        if (Integer.parseInt((String) holder.react_number.getText()) == 0)
                            holder.react_number.setVisibility(View.GONE);
                        else
                            holder.react_number.setVisibility(View.VISIBLE);

                        break;
                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });

        DatabaseReference reference3 = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");

        reference3.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {

                List<Chat> chatlist = new ArrayList<>();

                for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                    Chat temp = dataSnapshot.getValue(Chat.class);
                    chatlist.add(temp);
                }


                if (position == mChat.size() - 1) {
                    if (chat.isIsseen())
                        holder.txt_seen.setText("已讀");
                    else
                        holder.txt_seen.setText("已傳送");

                } else
                    holder.txt_seen.setVisibility(View.GONE);

                holder.send_time.setText(chat.getTime());
                holder.send_date.setText(chat.getDate());

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });


        holder.rr_layout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });


        holder.r_layout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.show_message.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.profile_image.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.txt_seen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });


        holder.send_time.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.send_date.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });


        holder.copy.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ClipboardManager myClipboard = (ClipboardManager) mContext.getSystemService(CLIPBOARD_SERVICE);
                ClipData myClip = ClipData.newPlainText("text", holder.show_message.getText().toString());
                myClipboard.setPrimaryClip(myClip);
                Toast.makeText(mContext.getApplicationContext(), "已複製", Toast.LENGTH_SHORT).show();
                holder.choice.setVisibility(View.GONE);
                GroupActivity.EmojiClear();
            }
        });

        holder.download.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new DownloadImage().execute(chat.getMessage());

                Toast.makeText(mContext.getApplicationContext(), "已下載", Toast.LENGTH_SHORT).show();
                holder.choice.setVisibility(View.GONE);
                GroupActivity.EmojiClear();
            }
        });

        holder.share.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                ShareAdapter.chat = chat;
                Intent Share = new Intent(mContext.getApplicationContext(), ShareActivity.class);
                mContext.startActivity(Share);

                holder.choice.setVisibility(View.GONE);
                GroupActivity.EmojiClear();
            }
        });


        holder.withdraw.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent event) {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        List<Chat> chatlist = new ArrayList<>();
                        for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                            Chat chat = dataSnapshot.getValue(Chat.class);
                            if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                HashMap<String, Object> hashMap = new HashMap<>();//
                                hashMap.put("message", "");//
                                dataSnapshot.getRef().updateChildren(hashMap);//

                                Toast.makeText(mContext.getApplicationContext(), "已收回", Toast.LENGTH_SHORT).show();
                                holder.choice.setVisibility(View.GONE);
                                break;
                            }
                        }
                        GroupActivity.EmojiClear();
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                    }
                });

                return true;
            }
        });


        holder.react_btn.setReactions(ReactionButton.reactions[0]);
        holder.react_btn.setDefaultReaction(ReactionButton.defaultReact_smile);
        holder.react_btn.setEnableReactionTooltip(true);
        holder.react_btn.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
                check = 1;
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        List<Chat> chatlist = new ArrayList<>();

                        if (holder.react_btn.getBackground().getConstantState() == view.getContext().getResources().getDrawable(R.drawable.blackground_sq_white).getConstantState()) {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_smile = chat.getEmoji_smile();

                                    if (check == 0)
                                        break;

                                    // 1
                                    emoji_smile += " ";
                                    emoji_smile += currentUserId;
                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_smile", emoji_smile);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_gray);
                                    chat.setEmoji_smile(emoji_smile);

                                    currentUserId = " " + currentUserId;

                                    // 2
                                    String emoji_love = chat.getEmoji_love();
                                    emoji_love = emoji_love.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_love", emoji_love);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_love(emoji_love);
                                    // 3
                                    String emoji_cry = chat.getEmoji_cry();
                                    emoji_cry = emoji_cry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_cry", emoji_cry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_cry(emoji_cry);
                                    // 4
                                    String emoji_angry = chat.getEmoji_angry();
                                    emoji_angry = emoji_angry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_angry", emoji_angry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_angry(emoji_angry);
                                    // 5
                                    String emoji_nothing = chat.getEmoji_nothing();
                                    emoji_nothing = emoji_nothing.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_nothing", emoji_nothing);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_nothing(emoji_nothing);
                                    // 6
                                    String emoji_good = chat.getEmoji_good();
                                    emoji_good = emoji_good.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_good", emoji_good);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_good(emoji_good);

                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        } else {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_smile = chat.getEmoji_smile();

                                    if (check == 0)
                                        break;

                                    currentUserId = " " + currentUserId;
                                    emoji_smile = emoji_smile.replaceAll(currentUserId, "");
                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_smile", emoji_smile);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_smile(emoji_smile);

                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                    }
                });

                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.react_btn2.setReactions(ReactionButton.reactions[1]);
        holder.react_btn2.setDefaultReaction(ReactionButton.defaultReact_love);
        holder.react_btn2.setEnableReactionTooltip(true);
        holder.react_btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
                check = 1;
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        List<Chat> chatlist = new ArrayList<>();

                        if (holder.react_btn2.getBackground().getConstantState() == view.getContext().getResources().getDrawable(R.drawable.blackground_sq_white).getConstantState()) {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_love = chat.getEmoji_love();

                                    if (check == 0)
                                        break;

                                    // 2
                                    emoji_love += " ";
                                    emoji_love += currentUserId;
                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_love", emoji_love);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_gray);
                                    chat.setEmoji_love(emoji_love);

                                    currentUserId = " " + currentUserId;

                                    // 1
                                    String emoji_smile = chat.getEmoji_smile();
                                    emoji_smile = emoji_smile.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_smile", emoji_smile);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_smile(emoji_smile);
                                    // 3
                                    String emoji_cry = chat.getEmoji_cry();
                                    emoji_cry = emoji_cry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_cry", emoji_cry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_cry(emoji_cry);
                                    // 4
                                    String emoji_angry = chat.getEmoji_angry();
                                    emoji_angry = emoji_angry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_angry", emoji_angry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_angry(emoji_angry);
                                    // 5
                                    String emoji_nothing = chat.getEmoji_nothing();
                                    emoji_nothing = emoji_nothing.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_nothing", emoji_nothing);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_nothing(emoji_nothing);
                                    // 6
                                    String emoji_good = chat.getEmoji_good();
                                    emoji_good = emoji_good.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_good", emoji_good);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_good(emoji_good);


                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        } else {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_love = chat.getEmoji_love();

                                    if (check == 0)
                                        break;

                                    currentUserId = " " + currentUserId;
                                    emoji_love = emoji_love.replaceAll(currentUserId, "");

                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_love", emoji_love);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_love(emoji_love);

                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                    }
                });

                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.react_btn3.setReactions(ReactionButton.reactions[2]);
        holder.react_btn3.setDefaultReaction(ReactionButton.defaultReact_cry);
        holder.react_btn3.setEnableReactionTooltip(true);
        holder.react_btn3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
                check = 1;
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        List<Chat> chatlist = new ArrayList<>();

                        if (holder.react_btn3.getBackground().getConstantState() == view.getContext().getResources().getDrawable(R.drawable.blackground_sq_white).getConstantState()) {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_cry = chat.getEmoji_cry();

                                    if (check == 0)
                                        break;

                                    // 3
                                    emoji_cry += " ";
                                    emoji_cry += currentUserId;
                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_cry", emoji_cry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_gray);
                                    chat.setEmoji_cry(emoji_cry);

                                    currentUserId = " " + currentUserId;

                                    // 1
                                    String emoji_smile = chat.getEmoji_smile();
                                    emoji_smile = emoji_smile.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_smile", emoji_smile);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_smile(emoji_smile);
                                    // 2
                                    String emoji_love = chat.getEmoji_love();
                                    emoji_love = emoji_love.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_love", emoji_love);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_love(emoji_love);
                                    // 4
                                    String emoji_angry = chat.getEmoji_angry();
                                    emoji_angry = emoji_angry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_angry", emoji_angry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_angry(emoji_angry);
                                    // 5
                                    String emoji_nothing = chat.getEmoji_nothing();
                                    emoji_nothing = emoji_nothing.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_nothing", emoji_nothing);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_nothing(emoji_nothing);
                                    // 6
                                    String emoji_good = chat.getEmoji_good();
                                    emoji_good = emoji_good.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_good", emoji_good);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_good(emoji_good);


                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        } else {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_cry = chat.getEmoji_cry();

                                    if (check == 0)
                                        break;

                                    currentUserId = " " + currentUserId;
                                    emoji_cry = emoji_cry.replaceAll(currentUserId, "");

                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_cry", emoji_cry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_cry(emoji_cry);

                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                    }
                });

                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.react_btn4.setReactions(ReactionButton.reactions[3]);
        holder.react_btn4.setDefaultReaction(ReactionButton.defaultReact_angry);
        holder.react_btn4.setEnableReactionTooltip(true);
        holder.react_btn4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
                check = 1;
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        List<Chat> chatlist = new ArrayList<>();

                        if (holder.react_btn4.getBackground().getConstantState() == view.getContext().getResources().getDrawable(R.drawable.blackground_sq_white).getConstantState()) {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_angry = chat.getEmoji_angry();

                                    if (check == 0)
                                        break;

                                    // 4
                                    emoji_angry += " ";
                                    emoji_angry += currentUserId;
                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_angry", emoji_angry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_gray);
                                    chat.setEmoji_angry(emoji_angry);

                                    currentUserId = " " + currentUserId;

                                    // 1
                                    String emoji_smile = chat.getEmoji_smile();
                                    emoji_smile = emoji_smile.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_smile", emoji_smile);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_smile(emoji_smile);
                                    // 2
                                    String emoji_love = chat.getEmoji_love();
                                    emoji_love = emoji_love.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_love", emoji_love);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_love(emoji_love);
                                    // 3
                                    String emoji_cry = chat.getEmoji_cry();
                                    emoji_cry = emoji_cry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_cry", emoji_cry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_cry(emoji_cry);
                                    // 5
                                    String emoji_nothing = chat.getEmoji_nothing();
                                    emoji_nothing = emoji_nothing.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_nothing", emoji_nothing);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_nothing(emoji_nothing);
                                    // 6
                                    String emoji_good = chat.getEmoji_good();
                                    emoji_good = emoji_good.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_good", emoji_good);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_good(emoji_good);


                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        } else {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_angry = chat.getEmoji_angry();

                                    if (check == 0)
                                        break;

                                    currentUserId = " " + currentUserId;
                                    emoji_angry = emoji_angry.replaceAll(currentUserId, "");

                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_angry", emoji_angry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_angry(emoji_angry);

                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                    }
                });

                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.react_btn5.setReactions(ReactionButton.reactions[4]);
        holder.react_btn5.setDefaultReaction(ReactionButton.defaultReact_nothing);
        holder.react_btn5.setEnableReactionTooltip(true);
        holder.react_btn5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
                check = 1;
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        List<Chat> chatlist = new ArrayList<>();

                        if (holder.react_btn5.getBackground().getConstantState() == view.getContext().getResources().getDrawable(R.drawable.blackground_sq_white).getConstantState()) {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_nothing = chat.getEmoji_nothing();

                                    if (check == 0)
                                        break;

                                    // 5
                                    emoji_nothing += " ";
                                    emoji_nothing += currentUserId;
                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_nothing", emoji_nothing);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_gray);
                                    chat.setEmoji_nothing(emoji_nothing);

                                    currentUserId = " " + currentUserId;

                                    // 1
                                    String emoji_smile = chat.getEmoji_smile();
                                    emoji_smile = emoji_smile.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_smile", emoji_smile);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_smile(emoji_smile);
                                    // 2
                                    String emoji_love = chat.getEmoji_love();
                                    emoji_love = emoji_love.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_love", emoji_love);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_love(emoji_love);
                                    // 3
                                    String emoji_cry = chat.getEmoji_cry();
                                    emoji_cry = emoji_cry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_cry", emoji_cry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_cry(emoji_cry);
                                    // 4
                                    String emoji_angry = chat.getEmoji_angry();
                                    emoji_angry = emoji_angry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_angry", emoji_angry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_angry(emoji_angry);
                                    // 6
                                    String emoji_good = chat.getEmoji_good();
                                    emoji_good = emoji_good.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_good", emoji_good);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_good(emoji_good);


                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        } else {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_nothing = chat.getEmoji_nothing();

                                    if (check == 0)
                                        break;

                                    currentUserId = " " + currentUserId;
                                    emoji_nothing = emoji_nothing.replaceAll(currentUserId, "");

                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_nothing", emoji_nothing);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_nothing(emoji_nothing);

                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                    }
                });

                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });

        holder.react_btn6.setReactions(ReactionButton.reactions[5]);
        holder.react_btn6.setDefaultReaction(ReactionButton.defaultReact_good);
        holder.react_btn6.setEnableReactionTooltip(true);
        holder.react_btn6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
                check = 1;
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        List<Chat> chatlist = new ArrayList<>();

                        if (holder.react_btn6.getBackground().getConstantState() == view.getContext().getResources().getDrawable(R.drawable.blackground_sq_white).getConstantState()) {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_good = chat.getEmoji_good();

                                    if (check == 0)
                                        break;

                                    // 6
                                    emoji_good += " ";
                                    emoji_good += currentUserId;
                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_good", emoji_good);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_gray);
                                    chat.setEmoji_good(emoji_good);

                                    currentUserId = " " + currentUserId;

                                    // 1
                                    String emoji_smile = chat.getEmoji_smile();
                                    emoji_smile = emoji_smile.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_smile", emoji_smile);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_smile(emoji_smile);
                                    // 2
                                    String emoji_love = chat.getEmoji_love();
                                    emoji_love = emoji_love.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_love", emoji_love);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn2.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_love(emoji_love);
                                    // 3
                                    String emoji_cry = chat.getEmoji_cry();
                                    emoji_cry = emoji_cry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_cry", emoji_cry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn3.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_cry(emoji_cry);
                                    // 4
                                    String emoji_angry = chat.getEmoji_angry();
                                    emoji_angry = emoji_angry.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_angry", emoji_angry);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn4.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_angry(emoji_angry);
                                    // 5
                                    String emoji_nothing = chat.getEmoji_nothing();
                                    emoji_nothing = emoji_nothing.replaceAll(currentUserId, "");
                                    hashMap.put("emoji_nothing", emoji_nothing);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn5.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_nothing(emoji_nothing);


                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        } else {
                            for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                                Chat chat = dataSnapshot.getValue(Chat.class);
                                assert chat != null;
                                if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                    String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                    String emoji_good = chat.getEmoji_good();

                                    if (check == 0)
                                        break;

                                    currentUserId = " " + currentUserId;
                                    emoji_good = emoji_good.replaceAll(currentUserId, "");

                                    HashMap<String, Object> hashMap = new HashMap<>();
                                    hashMap.put("emoji_good", emoji_good);
                                    dataSnapshot.getRef().updateChildren(hashMap);
                                    holder.react_btn6.setBackgroundResource(R.drawable.blackground_sq_white);
                                    chat.setEmoji_good(emoji_good);

                                    showEmoji(holder, chat);
                                    check = 0;
                                    break;
                                }
                            }
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                    }
                });

                GroupActivity.MessagegClear();
                GroupActivity.EmojiClear();
            }
        });


        holder.hide.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatabaseReference reference = FirebaseDatabase.getInstance().getReference("Groups").child(groupid).child("Chats");
                reference.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot snapshot) {
                        List<Chat> chatlist = new ArrayList<>();
                        for (DataSnapshot dataSnapshot : snapshot.getChildren()) {
                            Chat chat = dataSnapshot.getValue(Chat.class);
                            assert chat != null;
                            if (chat.getMessage().equals(holder.show_message.getText().toString()) && chat.getTime().equals(holder.send_time.getText().toString()) && chat.getDate().equals(holder.send_date.getText().toString())) {
                                String currentUserId = Objects.requireNonNull(FirebaseAuth.getInstance().getCurrentUser()).getUid();
                                String userCantSee = chat.getUserCantSee();

                                if (chat.getUserCantSee().contains(currentUserId))
                                    break;

                                userCantSee += " ";
                                userCantSee += currentUserId;

                                HashMap<String, Object> hashMap = new HashMap<>();
                                hashMap.put("userCantSee", userCantSee);
                                dataSnapshot.getRef().updateChildren(hashMap);

                                Toast.makeText(mContext.getApplicationContext(), "已隱藏", Toast.LENGTH_SHORT).show();
                                holder.choice.setVisibility(View.GONE);


                                break;
                            }
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                    }
                });
            }
        });

    }

    @Override
    public int getItemCount() {
        return mChat.size();
    }


    public class ViewHolder extends RecyclerView.ViewHolder {

        public TextView emoji_smile, emoji_love, emoji_cry, emoji_angry, emoji_nothing, emoji_good;
        public TextView react_number;
        public LinearLayout emoji;

        public TextView hide;
        public TextView copy;
        public TextView download;
        public TextView share;
        public TextView withdraw;
        public TextView show_message;
        public ImageButton show_image;
        public ImageView profile_image;
        public TextView username;
        public TextView txt_seen;
        public TextView send_time;
        public TextView send_date;
        public LinearLayout choice;
        public LinearLayout top;
        public RelativeLayout rr_layout;
        public RelativeLayout r_layout;

        public ReactButton react_btn, react_btn2, react_btn3, react_btn4, react_btn5, react_btn6;


        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            emoji = itemView.findViewById(R.id.emoji);

            emoji_smile = itemView.findViewById(R.id.emoji_smile);
            emoji_love = itemView.findViewById(R.id.emoji_love);
            emoji_cry = itemView.findViewById(R.id.emoji_cry);
            emoji_angry = itemView.findViewById(R.id.emoji_angry);
            emoji_nothing = itemView.findViewById(R.id.emoji_nothing);
            emoji_good = itemView.findViewById(R.id.emoji_good);
            username=itemView.findViewById(R.id.username);

            react_number = itemView.findViewById(R.id.react_number);

            react_btn = itemView.findViewById(R.id.react_btn);
            react_btn2 = itemView.findViewById(R.id.react_btn2);
            react_btn3 = itemView.findViewById(R.id.react_btn3);
            react_btn4 = itemView.findViewById(R.id.react_btn4);
            react_btn5 = itemView.findViewById(R.id.react_btn5);
            react_btn6 = itemView.findViewById(R.id.react_btn6);

            rr_layout = itemView.findViewById(R.id.rr_layout);
            r_layout = itemView.findViewById(R.id.r_layout);
            choice = itemView.findViewById(R.id.choice);
            show_message = itemView.findViewById(R.id.show_message);
            show_image = itemView.findViewById(R.id.send_Image);
            profile_image = itemView.findViewById(R.id.profile_image);
            txt_seen = itemView.findViewById(R.id.txt_seen);
            send_time = itemView.findViewById(R.id.send_time);
            send_date = itemView.findViewById(R.id.send_date);
            copy = itemView.findViewById(R.id.copy);
            download = itemView.findViewById(R.id.download);
            share = itemView.findViewById(R.id.share);
            withdraw = itemView.findViewById(R.id.withdraw);
            hide = itemView.findViewById(R.id.hide);
            top = itemView.findViewById(R.id.top);


            emoji_smile.setText(new String(Character.toChars(0x1F60A)));
            emoji_love.setText(new String(Character.toChars(0x1f60d)));
            emoji_cry.setText(new String(Character.toChars(0x1f62d)));
            emoji_angry.setText(new String(Character.toChars(0x1f621)));
            emoji_nothing.setText(new String(Character.toChars(0x1f636)));
            emoji_good.setText(new String(Character.toChars(0x1f44d)));


        }
    }


    @Override
    public int getItemViewType(int position) {
        fuser = FirebaseAuth.getInstance().getCurrentUser();
        if (mChat.get(position).getSender().equals(fuser.getUid()))
            return MSG_TYPE_RIGHT;
        else
            return MSG_TYPE_LEFT;
    }

}