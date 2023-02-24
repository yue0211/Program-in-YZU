package com.example.chatroom.Fragments;

import com.example.chatroom.Notifications.MyResponse;
import com.example.chatroom.Notifications.Sender;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.Headers;
import retrofit2.http.POST;

public interface APIService {

    @Headers(
            {

                "Content-Type:application/json",
                "Authorization:key=AAAAaQw7vxI:APA91bEIgBPrHKXt7v0mlBDpvRkLSA1tpLNf9G4wQyrIAiSOFX5WAsIBgyLpq4ReKWIQF-yeJ-niFN6WNQ0n7L3Wuiny1-G_MZ3xYfbyyumejdh0m3oGST1A_H9q9XTDhTccpfRu0ngc"

            }
    )

    @POST("fcm/send")
    Call<MyResponse> sendNotification(@Body Sender body);


}
