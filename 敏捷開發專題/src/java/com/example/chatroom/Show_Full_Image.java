package com.example.chatroom;

import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.squareup.picasso.Picasso;

public class Show_Full_Image extends AppCompatActivity {
    ImageButton imageButton;
    String url;
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {//捕捉返回鍵
        if ((keyCode == KeyEvent.KEYCODE_BACK)) {
            Show_Full_Image.this.finish();//關閉activity
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show_full_image);
        imageButton=findViewById(R.id.BigImage);
        Bundle bundle = getIntent().getExtras();
        if(bundle!=null){
            url=bundle.getString("u");
        }else{
            Toast.makeText(this, "錯誤", Toast.LENGTH_SHORT).show();
        }
        Picasso.get().load(url).into(imageButton);
        imageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                Show_Full_Image.this.finish();//關閉activity
            }
        });
    }
}