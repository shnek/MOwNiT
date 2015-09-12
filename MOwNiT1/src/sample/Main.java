package sample;

import javafx.application.Application;
import javafx.embed.swing.SwingFXUtils;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.layout.VBoxBuilder;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.scene.web.WebView;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.scene.Group;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;

public class Main extends Application {
    javafx.scene.image.ImageView iv1 = new javafx.scene.image.ImageView();

    @Override
    public void start(Stage primaryStage) throws Exception {

        Group root = new Group();
        Scene scene = new Scene(root);
        scene.setFill(Color.WHITE);
        javafx.scene.control.TextField startBox = new TextField();
        javafx.scene.control.TextField endBox = new TextField();
        javafx.scene.control.TextField step = new TextField();
        Text poczText = new Text(" Poczatek : ");
        Text konText = new Text(" Koniec : ");
        Text doklText = new Text(" Dokladnosc: ");
        Text funText = new Text(" Funckja: ");
        Button button = new Button(" View");
        Button refresh = new Button(" Refresh");
        VBox box = new VBox();
        HBox menu = new HBox();
        menu.alignmentProperty().set(Pos.CENTER);
        box.alignmentProperty().set(Pos.CENTER);

        final ComboBox priorityComboBox = new ComboBox();
        priorityComboBox.getItems().addAll(
                "E do X",
                "x^2",
                "lnx",
                "polynomial",
                "nierozniczkowalna",
                "nierozniczkowalna2",
                "nieroz3"
        );
        WebView wv = new WebView();


        menu.getChildren().add(button);
        menu.getChildren().add(poczText);
        menu.getChildren().add(startBox);
        menu.getChildren().add(konText);
        menu.getChildren().add(endBox);
        menu.getChildren().add(funText);
        menu.getChildren().add(priorityComboBox);
        menu.getChildren().add(doklText);
        menu.getChildren().add(step);
        box.getChildren().add(menu);
        box.getChildren().add(wv);
        root.getChildren().add(box);
        primaryStage.setTitle("Projekt1");
        primaryStage.setResizable(true);
        primaryStage.setScene(scene);
        primaryStage.sizeToScene();
        box.prefHeightProperty().bind(primaryStage.heightProperty());
        box.prefWidthProperty().bind(primaryStage.widthProperty());
        wv.prefHeightProperty().bind(box.heightProperty());
        primaryStage.setMinWidth(1200);
        primaryStage.setMinHeight(600);
        wv.setMaxHeight(1000);
        wv.setMaxWidth(1900);


        primaryStage.show();
        button.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                if (startBox.getText() == null && endBox.getText() == null) {
                    return;
                }
                System.out.println("Running with " + startBox.getText() + " " + endBox.getText());
                int fno = 2;
                if (priorityComboBox.getValue() == "E do X") {
                    fno = 1;
                } else if (priorityComboBox.getValue() == "x^2") {
                    fno = 2;
                } else if (priorityComboBox.getValue() == "lnx") {
                    fno = 3;
                } else if (priorityComboBox.getValue() == "polynomial") {
                    fno = 4;
                } else if (priorityComboBox.getValue() == "nierozniczkowalna") {
                    fno = 5;
                } else if (priorityComboBox.getValue() == "nierozniczowalna2") {
                    fno = 6;
                } else if (priorityComboBox.getValue() == "nieroz3") {
                    fno = 7;
                }
                if (startBox.getText().isEmpty() || endBox.getText().isEmpty() || step.getText().isEmpty()) {
                    showError("Wrong arguments!");
                } else {
                    runProgram(Integer.parseInt(startBox.getText()), Integer.parseInt(endBox.getText()), fno, Double.parseDouble(step.getText()));
                    try {
                        File imagefile2 = new File("/home/kuba/IdeaProjects/MOwNiT1/C/data.svg");
                        wv.getEngine().load(imagefile2.toURL().toString());
                    } catch (MalformedURLException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        refresh.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                try {
                    File imagefile = new File("/home/kuba/IdeaProjects/MOwNiT1/C/data.png");
                    BufferedImage bf = ImageIO.read(imagefile);
                    Image image = SwingFXUtils.toFXImage(bf, null);
                    iv1.setImage(image);
                } catch (MalformedURLException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    private void showError(String text) {
        Stage dialogStage = new Stage();
        dialogStage.initModality(Modality.WINDOW_MODAL);
        dialogStage.setScene(new Scene(VBoxBuilder.create().
                children(new Text(text), new Button("Ok.")).
                alignment(Pos.CENTER).padding(new Insets(5)).build()));
        dialogStage.show();
    }

    private static int runProgram(int start, int end, int fun, double step) {
        execl("./C/zad " + start + " " + end + " " + fun + " " + step);
        execl("Rscript C/Rscript.txt");
        return 0;

    }

    private static void execl(String line) {
        String s;
        Process p;
        try {
            System.out.println("trying to run!");
            p = Runtime.getRuntime().exec(line);
            BufferedReader br = new BufferedReader(
                    new InputStreamReader(p.getInputStream())
            );
            while ((s = br.readLine()) != null)
                System.out.println("line: " + s);
            p.waitFor();
            System.out.println("exit:" + p.exitValue());
            p.destroy();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
