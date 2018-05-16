package medialibrary;

public class BoPlayer {
    private long instanceId;
    private String url;


    public BoPlayer(int instanceId, String url){
        this.instanceId = instanceId;
        this.url = url;
    }

    public void setUrl(String url){
        this.url = url;
    }

}
