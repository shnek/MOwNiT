package sample;

import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
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
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
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
import java.io.*;
import java.net.MalformedURLException;
import java.util.ArrayList;

public class Main extends Application {
    javafx.scene.image.ImageView iv1 = new javafx.scene.image.ImageView();
    int xpos, ypos;
    ArrayList<File> plots = new ArrayList<File>();

    @Override
    public void start(Stage primaryStage) throws Exception {

        Group root = new Group();
        Scene scene = new Scene(root);
        scene.setFill(Color.WHITE);
        javafx.scene.control.TextField startBox = new TextField();
        javafx.scene.control.TextField endBox = new TextField();
        javafx.scene.control.TextField step = new TextField();
        TextField a = new TextField();
        TextField b = new TextField();
        TextField c = new TextField();
        TextField d = new TextField();
        TextField punktfield = new TextField();
        a.setPrefWidth(50);
        b.setPrefWidth(50);
        c.setPrefWidth(50);
        d.setPrefWidth(50);
        punktfield.setPrefWidth(50);
        Text poczText = new Text(" Poczatek : ");
        Text konText = new Text(" Koniec : ");
        Text doklText = new Text(" Dokladnosc: ");
        Text funText = new Text(" Funckja: ");
        Button button = new Button(" View");
        Button refresh = new Button(" Refresh");
        Text atext = new Text(" a : ");
        Text btext = new Text(" b : ");
        Text ctext = new Text(" c : ");
        Text dtext = new Text(" d : ");
        Text punkts = new Text(" p : ");
        VBox box = new VBox();
        HBox menu = new HBox();
        HBox menu2 = new HBox();
        menu.alignmentProperty().set(Pos.CENTER);
        menu2.alignmentProperty().set(Pos.CENTER);
        box.alignmentProperty().set(Pos.CENTER);


        final ComboBox priorityComboBox = new ComboBox();
        priorityComboBox.getItems().addAll(
                "bisection", "falsepos", "brent", "newton", "secant", "steffenson"
        );
        WebView wv = new WebView();

        Slider slider = new Slider();
        slider.setValue(0);
        slider.setShowTickLabels(true);
        slider.setShowTickMarks(true);
        slider.setMajorTickUnit(1);
        slider.setMinorTickCount(1);
        slider.setBlockIncrement(1);
        slider.setMin(0);
        slider.setMax(0);
        slider.setPrefWidth(1000);
        menu.getChildren().add(button);
        menu.getChildren().add(poczText);
        menu.getChildren().add(startBox);
        menu.getChildren().add(konText);
        menu.getChildren().add(endBox);
        menu.getChildren().add(funText);
        menu.getChildren().add(priorityComboBox);
        menu.getChildren().add(doklText);
        menu.getChildren().add(step);
        menu.getChildren().add(atext);
        menu.getChildren().add(a);
        menu.getChildren().add(btext);
        menu.getChildren().add(b);
        menu.getChildren().add(ctext);
        menu.getChildren().add(c);
        menu.getChildren().add(dtext);
        menu.getChildren().add(d);
        menu.getChildren().add(punkts);
        menu.getChildren().add(punktfield);
        menu2.getChildren().add(slider);
        box.getChildren().add(menu);
        box.getChildren().add(menu2);
        box.setAlignment(Pos.CENTER);
        box.getChildren().add(wv);
        root.getChildren().add(box);
        primaryStage.setTitle("Znajdowanie pierwiastkow");
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
//        wv.disableProperty().


        wv.setOnScroll(new EventHandler<ScrollEvent>() {
            @Override
            public void handle(ScrollEvent event) {
                if (event.getDeltaY() > 0) {
                    wv.setZoom(wv.getZoom() + 0.1);
                } else {
                    wv.setZoom(wv.getZoom() - 0.1);
                }

            }
        });


        primaryStage.show();
        button.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                if (startBox.getText() == null && endBox.getText() == null) {
                    return;
                }
                System.out.println("Running with " + startBox.getText() + " " + endBox.getText());
                int fno = 0;
                boolean deriv = false;
                if (priorityComboBox.getValue() == "bisection") {
                    fno = 1;
                } else if (priorityComboBox.getValue() == "falsepos") {
                    fno = 2;
                } else if (priorityComboBox.getValue() == "brent") {
                    fno = 3;
                } else if (priorityComboBox.getValue() == "newton") {
                    fno = 4;
                    deriv = true;
                } else if (priorityComboBox.getValue() == "secant") {
                    fno = 5;
                    deriv = true;
                } else if (priorityComboBox.getValue() == "steffenson") {
                    fno = 6;
                    deriv = true;
                }
                if (startBox.getText().isEmpty() || endBox.getText().isEmpty() || step.getText().isEmpty() || fno == 0) {
                    showError("Wrong arguments!");
                } else {
                    runProgram(Integer.parseInt(startBox.getText()), Integer.parseInt(endBox.getText()), fno, Double.parseDouble(step.getText()), Double.parseDouble(a.getText()), Double.parseDouble(b.getText()), Double.parseDouble(c.getText()), Double.parseDouble(d.getText()), Double.parseDouble(punktfield.getText()));
                    int count = countLines();
                    slider.setMax(count);
                    while (!plots.isEmpty()) {
                        plots.remove(0);
                    }
                    for (int i = 0; i <= count; i++) {
                        plotNumber(deriv, i);
                        plots.add(new File("/home/kuba/IdeaProjects/MOwNiT2/C/data" + i + ".svg"));
                    }
                    try {
                        if(count != 0){
                            wv.getEngine().load(plots.get(0).toURL().toString());
                        }else{
                            slider.disabledProperty();
                            showError("This method did not work!");
                            wv.getEngine().load(null);
                        }

                        slider.setValue(0);
                    } catch (MalformedURLException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        slider.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
                try {
                    wv.getEngine().load(plots.get(newValue.intValue()).toURL().toString());
                } catch (MalformedURLException e) {
                    e.printStackTrace();
                }
            }
        });

    }

    private int countLines() {
        int i = -1;
        try {
            BufferedReader file = new BufferedReader(new FileReader("/home/kuba/IdeaProjects/MOwNiT2/C/results.txt"));
            while (file.readLine() != null) {
                i++;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return i;
    }

    private void showError(String text) {
        Stage dialogStage = new Stage();
        dialogStage.initModality(Modality.WINDOW_MODAL);
        dialogStage.setScene(new Scene(VBoxBuilder.create().
                children(new Text(text)).
                alignment(Pos.CENTER).padding(new Insets(5)).build()));

        dialogStage.show();
    }

    private static void plotNumber(boolean deriv, int i) {
        System.out.println("Rscript: ");
        if(deriv){
            execl("Rscript ./C/Rscriptdf.txt " + i);
        }else{
            execl("Rscript ./C/Rscript.txt " + i);
        }
    }

    private static int runProgram(int start, int end, int fun, double step, double a, double b, double c, double d, double startpoint) {
        System.out.println(" !!! --- executing program --- !!!" + fun);
        execl("./C/zad " + fun + " " + start + " " + end + " " + a + " " + b + " " + c + " " + d + " " + step + " " + startpoint);
        return 0;
    }

    private static void execl(String line) {
        String s;
        Process p;
        try {
//            System.out.println("trying to run!");
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
