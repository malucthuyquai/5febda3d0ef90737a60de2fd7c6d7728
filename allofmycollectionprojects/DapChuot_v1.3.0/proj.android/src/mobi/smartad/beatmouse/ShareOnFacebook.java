package mobi.smartad.beatmouse;


import java.io.ByteArrayOutputStream;
import java.io.File;

import com.facebook.AppEventsLogger;
import com.facebook.FacebookAuthorizationException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.FacebookRequestError;
import com.facebook.LoggingBehavior;
import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.Settings;
import com.facebook.UiLifecycleHelper;
import com.facebook.android.Facebook;
import com.facebook.model.GraphObject;
import com.facebook.widget.FacebookDialog;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.location.Location;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

public class ShareOnFacebook extends Activity{
	private String messageToPost;
	private String imagePath;
	private Session.StatusCallback statusCallback = new SessionStatusCallback();
	private static final String PERMISSION = "publish_actions";
	private final String PENDING_ACTION_BUNDLE_KEY = "com.facebook.samples.hellofacebook:PendingAction";
	private PendingAction pendingAction = PendingAction.NONE;
	private enum PendingAction {
        NONE,
        POST_PHOTO,
        POST_STATUS_UPDATE
    }
	private UiLifecycleHelper uiHelper;
	private Session.StatusCallback callback = new Session.StatusCallback() {
        @Override
        public void call(Session session, SessionState state, Exception exception) {
            onSessionStateChange(session, state, exception);
        }
    };
    private FacebookDialog.Callback dialogCallback = new FacebookDialog.Callback() {
        @Override
        public void onError(FacebookDialog.PendingCall pendingCall, Exception error, Bundle data) {
            Log.d("HelloFacebook", String.format("Error: %s", error.toString()));
        }
        @Override
        public void onComplete(FacebookDialog.PendingCall pendingCall, Bundle data) {
            Log.d("HelloFacebook", "Success!");
        }
    };

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		uiHelper = new UiLifecycleHelper(this, callback);
        uiHelper.onCreate(savedInstanceState);

        if (savedInstanceState != null) {
            String name = savedInstanceState.getString(PENDING_ACTION_BUNDLE_KEY);
            pendingAction = PendingAction.valueOf(name);
        }

		Settings.addLoggingBehavior(LoggingBehavior.INCLUDE_ACCESS_TOKENS);

        Session session = Session.getActiveSession();
        if (session == null) {
            if (savedInstanceState != null) {
                session = Session.restoreSession(this, null, statusCallback, savedInstanceState);
            }
            if (session == null) {
                session = new Session(this);
            }
            Session.setActiveSession(session);
            if (session.getState().equals(SessionState.CREATED_TOKEN_LOADED)) {
                session.openForRead(new Session.OpenRequest(this).setCallback(statusCallback));
            }
        }

		requestWindowFeature(Window.FEATURE_NO_TITLE);

		setContentView(R.layout.facebook_dialog);
		
		String facebookMessage = getIntent().getStringExtra("facebookMessage");
		imagePath = getIntent().getStringExtra("imagePath");
		if (facebookMessage == null){
			facebookMessage = "Test wall post";
		}
		messageToPost = facebookMessage;
		
		ImageView imgview = (ImageView) findViewById(R.id.share_thumb);
		File f = new File(imagePath);
		Bitmap bmp = BitmapFactory.decodeFile(f.getAbsolutePath());
		imgview.setImageBitmap(bmp);
	}
	
	@Override
    public void onStart() {
        super.onStart();
        Session.getActiveSession().addCallback(statusCallback);
    }

    @Override
    public void onStop() {
        super.onStop();
        Session.getActiveSession().removeCallback(statusCallback);
    }
    
    @Override
    public void onPause() {
        super.onPause();
        uiHelper.onPause();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        uiHelper.onDestroy();
    }
    
    @Override
    protected void onResume() {
        super.onResume();
        uiHelper.onResume();
        AppEventsLogger.activateApp(this);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        uiHelper.onActivityResult(requestCode, resultCode, data, dialogCallback);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        uiHelper.onSaveInstanceState(outState);
        outState.putString(PENDING_ACTION_BUNDLE_KEY, pendingAction.name());
        Session session = Session.getActiveSession();
        Session.saveSession(session, outState);
    }
    
    private void onSessionStateChange(Session session, SessionState state, Exception exception) {
        if (pendingAction != PendingAction.NONE &&
                (exception instanceof FacebookOperationCanceledException ||
                exception instanceof FacebookAuthorizationException)) {
        	showToast("Error" + exception);
                new AlertDialog.Builder(ShareOnFacebook.this)
                    .setTitle("Canceled")
                    .setMessage("Permission not granted")
                    .setPositiveButton("OK", null)
                    .show();
            pendingAction = PendingAction.NONE;
        } else if (state == SessionState.OPENED_TOKEN_UPDATED) {
            handlePendingAction();
        }
    }
    
    @SuppressWarnings("incomplete-switch")
    private void handlePendingAction() {
    	Log.d("share", "handle publish");
        PendingAction previouslyPendingAction = pendingAction;
        // These actions may re-set pendingAction if they are still pending, but we assume they
        // will succeed.
        pendingAction = PendingAction.NONE;

        switch (previouslyPendingAction) {
            case POST_PHOTO:
                postPhoto();
                break;
            case POST_STATUS_UPDATE:
                //postStatusUpdate();
                break;
        }
    }
    
    private void postPhoto() {
        if (hasPublishPermission()) {
        	File f = new File(imagePath);
        	Bitmap image = BitmapFactory.decodeFile(f.getAbsolutePath());
            Request request = Request.newUploadPhotoRequest(Session.getActiveSession(), image, new Request.Callback() {
                @Override
                public void onCompleted(Response response) {
                    Log.d("response", "rresponse = " + response);
                    showToast("Successfully posted");
                }
            });
            Bundle params = request.getParameters();
            EditText text = (EditText) findViewById(R.id.share_text);
            params.putString("name", text.getText().toString());
            request.setParameters(params);
            request.executeAsync();
            finish();
        } else {
            pendingAction = PendingAction.POST_PHOTO;
        }
    }
    
    private boolean hasPublishPermission() {
        Session session = Session.getActiveSession();
        return session != null && session.getPermissions().contains("publish_actions");
    }
    
    private void performPublish(PendingAction action, boolean allowNoSession) {
    	Log.d("share", "perform");
        Session session = Session.getActiveSession();
        if (session != null) {
        	Log.d("share", "session");
            pendingAction = action;
            if (hasPublishPermission()) {
                // We can do the action right away.
                handlePendingAction();
                return;
            } else if (session.isOpened()) {
            	Log.d("share", "opened");
                // We need to get new permissions, then complete the action when we get called back.
                session.requestNewPublishPermissions(new Session.NewPermissionsRequest(this, PERMISSION));
                return;
            } else {
            	Log.d("share", "login 1");
            	fbLogin();
            }
        } else {
        	Log.d("share", "login 2");
        	fbLogin();
        }

        if (allowNoSession) {
        	Log.d("share", "no sessiojn");
            pendingAction = action;
            handlePendingAction();
        }
    }

	public void doNotShare(View button){
		finish();
	}
	public void share(View button){
		Log.d("share", "share");
		performPublish(PendingAction.POST_PHOTO, false);
	}
	
	private void fbLogin() {
        Session session = Session.getActiveSession();
        if (!session.isOpened() && !session.isClosed()) {
            session.openForRead(new Session.OpenRequest(this).setCallback(statusCallback));
        } else {
            Session.openActiveSession(this, true, statusCallback);
        }
    }
	
	private void showPublishResult(String message, GraphObject result, FacebookRequestError error) {
        String title = null;
        String alertMessage = null;
        if (error == null) {
            title = "Success";
            String id = result.cast(GraphObjectWithId.class).getId();
            alertMessage = "Successfully posted" + message + id;
        } else {
            title = "Error";
            alertMessage = error.getErrorMessage();
        }

        new AlertDialog.Builder(this)
                .setTitle(title)
                .setMessage(alertMessage)
                .setPositiveButton("OK", null)
                .show();
    }
	
	private interface GraphObjectWithId extends GraphObject {
        String getId();
    }

	private void showToast(String message){
		Toast.makeText(getApplicationContext(), message, Toast.LENGTH_SHORT).show();
	}
	
	private class SessionStatusCallback implements Session.StatusCallback {
        @Override
        public void call(Session session, SessionState state, Exception exception) {
        	Log.d("dsaf", "session" + session + " state" + state + " ex" + exception);
        	onSessionStateChange(session, state, exception);
        }
    }
	
	private void showAlert(String title, String message) {
        new AlertDialog.Builder(this)
                .setTitle(title)
                .setMessage(message)
                .setPositiveButton("OK", null)
                .show();
    }
}
