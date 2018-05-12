/* -*- Mode: java; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * xscreensaver, Copyright (c) 2016 Jamie Zawinski <jwz@jwz.org>
 * and Dennis Sheil <dennis@panaceasupplies.com>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or 
 * implied warranty.
 *
 * This is the XScreenSaver "application" that just brings up the
 * Live Wallpaper preferences.
 */

package org.jwz.xscreensaver;

import android.app.Activity;
import android.app.WallpaperManager;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.provider.Settings;

public class XScreenSaverActivity extends Activity {

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    openList();
    setContentView(R.layout.activity_xscreensaver);

    findViewById(R.id.apply_wallpaper)
      .setOnClickListener(new View.OnClickListener() {
          @Override
          public void onClick(View v) {
              openList();
          }
      });

  }

  private void openList() {
    Intent intent;
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2) {
        intent = new Intent(Settings.ACTION_DREAM_SETTINGS);
    } else {
        intent = new Intent(Settings.ACTION_DISPLAY_SETTINGS);
    }
    startActivity(intent);
  }

}
