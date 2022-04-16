package com.example.dms;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class GeneralAdminHome extends AppCompatActivity {
    private String GAId;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.general_admin_home);
        Intent intent = getIntent();
        GAId=intent.getStringExtra("GAId");

        Button buildingBuild = (Button)findViewById(R.id.buildingBuild);
        buildingBuild.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(GeneralAdminHome.this, GeneralAdminBuildingBuild.class);
                startActivity(intent);
            }
        });

        Button buildingAbandon = (Button)findViewById(R.id.buildingAbandon);
        buildingAbandon.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(GeneralAdminHome.this, GeneralAdminBuildingAbandon.class);
                startActivity(intent);
            }
        });
    }

    public void navigationMy(View view){
        Intent intent = new Intent(GeneralAdminHome.this, GeneralAdminMy.class);
        intent.putExtra("GAId",GAId);
        startActivity(intent);
    }

}
