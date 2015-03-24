/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package mobi.smartad.beatmouse;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.flurry.android.FlurryAgent;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.FrameLayout;
import android.widget.Toast;

import com.google.android.gms.games.Games;

import mobi.smartad.beatmouse.basegameutils.GameHelper;
import mobi.smartad.beatmouse.basegameutils.GameHelper.GameHelperListener;

@SuppressLint("ShowToast")
public class BeatMouse extends Cocos2dxActivity {
	private AdView adView;
	private static final String ADMOB_ID = "a1530e0bd518507";
	private static final String LB_ID = "CgkIsqzKi5McEAIQAQ";
	private boolean admobAdded;
	public static GameHelper mHelper;
	public static Activity weekSelf;
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		weekSelf = this;
		mHelper = new GameHelper(this, GameHelper.CLIENT_ALL);
		if (true) {
	        //mHelper.enableDebugLog(true, "GameHelper");
	    }
		GameHelperListener listener = new GameHelper.GameHelperListener() {
			@Override
			public void onSignInFailed() {
				// TODO Auto-generated method stub
				Log.d("", "Signin failed");
			}
			@Override
			public void onSignInSucceeded() {
				// TODO Auto-generated method stub
				Log.d("", "Signin succeeded");
			}
	    };
	    mHelper.setup(listener);
		try {
			admobAdded = false;
			final FrameLayout.LayoutParams adsParams = new FrameLayout.LayoutParams(
					FrameLayout.LayoutParams.MATCH_PARENT, 
					FrameLayout.LayoutParams.WRAP_CONTENT, 
					android.view.Gravity.BOTTOM|android.view.Gravity.CENTER_HORIZONTAL);
			AdRequest adRequest = new AdRequest.Builder().build();
			adView = new AdView(BeatMouse.this);
			adView.setAdUnitId(ADMOB_ID);
			adView.setAdSize(AdSize.SMART_BANNER);
			adView.setAdListener(new AdListener() {
				@Override
				public void onAdLoaded() {
					try {
						if(admobAdded == false) addContentView(adView, adsParams);
					} catch (Exception ex) {
						Log.d("", ex.toString());
					}
					admobAdded = true;
				}
			});
			adView.loadAd(adRequest);
		} catch (Exception e) {
			Log.d("", "error: " + e);
		}
	}
    static void submitScore(float score) {
    	if(mHelper.isSignedIn()) {
    		Games.Leaderboards.submitScore(mHelper.getApiClient(), LB_ID, (long) score);
    	} else {
    		setAuth("Login failed", getContext().getApplicationContext());
    	}
    }
    public static void setAuth(final String str, Context context) {
    	weekSelf.runOnUiThread(new Runnable() {
    		public void run() {
    		    Toast.makeText(weekSelf, str, Toast.LENGTH_SHORT).show();
    		}
    	});
    }
    static void showLeaderBoard() {
    	if(mHelper.isSignedIn()) {
    		weekSelf.startActivityForResult(Games.Leaderboards.getLeaderboardIntent(mHelper.getApiClient(), LB_ID), 1);
    	} else {
    		setAuth("Login failed", getContext().getApplicationContext());
    	}
    }
    static void shareFacebook(String path) {
    	Log.d("fdsf", path);
    	Intent intent = new Intent(weekSelf, ShareOnFacebook.class);
    	intent.putExtra("imagePath", path);
    	weekSelf.startActivity(intent);
    }
    @Override
    public void onResume() {
      super.onResume();
      if (adView != null) {
        adView.resume();
      }
    }

    @Override
    public void onPause() {
      if (adView != null) {
        adView.pause();
      }
      super.onPause();
    }

    /** Called before the activity is destroyed. */
    @Override
    public void onDestroy() {
      // Destroy the AdView.
      if (adView != null) {
        adView.destroy();
      }
      super.onDestroy();
    }
    @Override
    protected void onActivityResult(int request, int response, Intent data) {
        super.onActivityResult(request, response, data);
        mHelper.onActivityResult(request, response, data);
    }
    //Flurry analytics
    protected void onStart() {
    	super.onStart();
    	mHelper.onStart(this);
    	FlurryAgent.onStartSession(BeatMouse.this, "7H9PQP8GDMYFXF4N34DX");
    }
  //Flurry analytics
    protected void onStop() {
    	super.onStop();
    	mHelper.onStop();
    	FlurryAgent.onEndSession(BeatMouse.this);
    }
    
    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
    
}
