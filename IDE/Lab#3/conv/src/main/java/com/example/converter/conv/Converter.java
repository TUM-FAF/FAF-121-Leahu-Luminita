package com.example.converter.conv;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class Converter extends Activity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_converter); // R - automatically generated, link from xml file ( all layouts)

        final EditText editC = (EditText) findViewById(R.id.editC);
        final EditText editM = (EditText) findViewById(R.id.editM);

        Button buttonConvert = (Button) findViewById(R.id.buttonConvert);
        Button buttonAbout   = (Button) findViewById(R.id.buttonAbout);

        buttonConvert.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View arg0)
            {
                String value = editC.getText().toString();

                double centimeters = Double.valueOf(value);

                double metres = centimeters * 0.01;

                editM.setText(String.valueOf(metres));
            }
        });

        buttonAbout.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                startActivity(new Intent(getApplicationContext(), About.class));
            }
        });
    }




}
