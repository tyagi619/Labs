// import packages from java
import java.awt.Color;
import java.awt.event.*;
import java.awt.*;
import java.util.concurrent.TimeUnit;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.swing.JButton;
import javax.swing.Timer;


public class calculator extends javax.swing.JFrame {

    // Variables declaration for GUI elements
    JButton[] btn = new JButton[10]; //numeric button
    JButton[] op = new JButton[5];   // operator button
    private javax.swing.JTextField displayBox; // display box
    JButton clear;  //AC Button
    // End of variables declaration//GEN-END:variables

    // true means operator is to be highlighted. false means numeric has to be highlighted
    boolean isOperator;
    // true means that the result is displayed. False means still waiting for user to select choices    
    boolean complete;
    // Numeric key that is currently being highlighted
    int numIndex;
    // Operator key that is currently being highlighted
    int opIndex;
    // String storing the text to be displayed on calculator screen
    String displayString;
    // Array of possible operator inputs
    char[] operator = {'=','-','*','/','+'};

    // Constructor for calculator class
    public calculator() {
        initComponents(); // initialise the gui for the calculator
        // Initialise the various variables of calculator class
        isOperator = false;
        complete = false;
        numIndex = 0;
        opIndex = 0;
        displayString = "";
    }

    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        // This handles all the warnings and errors that may occur in GUI
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        
        // Create a object of class calculator
        calculator calc = new calculator();
        // Display the calculator on screen
        calc.setVisible(true);

        // Define a timer function that calls every 1.5s and changes the current highlight key
        Timer timer = new Timer(1500, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                // If the result is displayed
                if(calc.complete){
                    // highlight the 'AC' button for user selection
                    calc.selectButton(calc.clear);
                    // de-highlight the currently highlighted numeric button
                    calc.deselectButton(calc.btn[calc.numIndex]);
                    // de-highlight the currently highlighted operator button
                    calc.deselectButton(calc.op[calc.opIndex]);
                }
                else{
                    // Highlight the next operator button and
                    // de-highlight the previously highlighted operator button
                    calc.deselectButton(calc.op[calc.opIndex]);
                    calc.opIndex = (calc.opIndex+1)%5;
                    calc.selectButton(calc.op[calc.opIndex]);
                    // Highlight the next numeric button and 
                    // de-highlight the previously highlighted numeric button 
                    calc.deselectButton(calc.btn[calc.numIndex]);
                    calc.numIndex = (calc.numIndex+1)%10;
                    calc.selectButton(calc.btn[calc.numIndex]);
                }
            }
        });
        // Set timer to repeat function call after every 1.5s
        timer.setRepeats(true);
        // start the timer
        timer.start();
    }

    // Function sets the background color of the button to white
    public void deselectButton(JButton btn){
        btn.setBackground(Color.WHITE);
    }

    // Function sets the background color of button to yellow
    public void selectButton(JButton btn){
        btn.setBackground(Color.YELLOW);
    }

    // Evaluates the user query and produces output
    // Uses Nashorm engine to evaluate the string query
    public void evaluate() throws ScriptException{
        // create a new instance of Nashorm engine
        ScriptEngineManager manager = new ScriptEngineManager();
        ScriptEngine engine = manager.getEngineByName("js");
        // uses 'eval' function to evaluate the output
        Object result = engine.eval(displayString);
        // Display the result to the user screen
        displayString = result.toString();
        displayBox.setText(displayString);
    }

    // Defines a key press event
    public KeyListener keyPress(){
        return new KeyListener() {
            // When key is pressed
            public void keyPressed(KeyEvent e){
                // if 'ENTER' is pressed and '=' is not selected
                if(e.getKeyCode()==KeyEvent.VK_ENTER && !complete){
                    // append the current numeric highlighted key value to the display string
                    displayString += Integer.toString(numIndex);
                    // the user can input an operator after an operand
                    isOperator = true;
                }
                // if 'SPACE' is pressed and operator input is allowed
                else if(e.getKeyCode()==KeyEvent.VK_SPACE && !complete && isOperator){
                    // if '=' is selected
                    if(opIndex==0){
                        // compute the final answer. Call the evaluate function
                        // that evaluates mathematical expression
                        try{
                            evaluate();
                        }
                        catch(ScriptException err){
                        }
                        // set complete to true since output is ready to be displayed
                        complete = true;
                    }
                    // if any other operator is selected
                    else{
                        // append the operator to the display string
                        displayString += operator[opIndex];
                    }
                    // An operator cannot proceed an operator. Set isOperator to 'false'
                    isOperator = false;
                }
                // if 'AC' is highlighted and 'ENTER' or 'SPACE' is pressed
                else if((e.getKeyCode()==KeyEvent.VK_ENTER || e.getKeyCode()==KeyEvent.VK_SPACE) && complete){
                    // de-highlight the 'AC' button
                    deselectButton(clear);
                    // Clear the display string
                    displayString = "";
                    // set complete to false
                    complete = false;
                    // set isOperator to false
                    isOperator = false;
                    numIndex = 0;
                    opIndex = 0;
                }
                // display the displayString on the screen
                displayBox.setText(displayString);
            }
            // When key is released
            public void keyReleased(KeyEvent e) {
            }
            // When key is Typed
            public void keyTyped(KeyEvent e) {
            }
        };
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * The content of this method is always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // This auto-generated code for GUI using Netbeans 12.1
    private void initComponents() {
        // Initialise the various components of the form
        displayBox = new javax.swing.JTextField(); // Text field to display output
        // 'AC' button 
        clear = new javax.swing.JButton();
        // numeric buttons
        btn[1] = new javax.swing.JButton();
        btn[2] = new javax.swing.JButton();
        btn[3] = new javax.swing.JButton();
        btn[4] = new javax.swing.JButton();
        btn[5] = new javax.swing.JButton();
        btn[6] = new javax.swing.JButton();
        btn[7] = new javax.swing.JButton();
        btn[8] = new javax.swing.JButton();
        btn[9] = new javax.swing.JButton();
        btn[0] = new javax.swing.JButton();
        // Operator Buttons
        op[1] = new javax.swing.JButton();
        op[2] = new javax.swing.JButton();
        op[3] = new javax.swing.JButton();
        op[4] = new javax.swing.JButton();
        op[0] = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        // The following code sets the properties of various GUI components
        // This cpde is auto-generated when creating GUI using Netbeans 12.1
        displayBox.setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        displayBox.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        displayBox.setEditable(false);
        displayBox.addKeyListener(keyPress());

        clear.setBackground(new java.awt.Color(255, 255, 255));
        clear.setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        clear.setText("AC");
        clear.addKeyListener(keyPress());

        btn[1].setBackground(new java.awt.Color(255, 255, 255));
        btn[1].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[1].setText("1");
        btn[1].addKeyListener(keyPress());

        btn[2].setBackground(new java.awt.Color(255, 255, 255));
        btn[2].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[2].setText("2");
        btn[2].addKeyListener(keyPress());

        btn[3].setBackground(new java.awt.Color(255, 255, 255));
        btn[3].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[3].setText("3");
        btn[3].addKeyListener(keyPress());

        btn[4].setBackground(new java.awt.Color(255, 255, 255));
        btn[4].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[4].setText("4");
        btn[4].addKeyListener(keyPress());

        btn[5].setBackground(new java.awt.Color(255, 255, 255));
        btn[5].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[5].setText("5");
        btn[5].addKeyListener(keyPress());

        btn[6].setBackground(new java.awt.Color(255, 255, 255));
        btn[6].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[6].setText("6");
        btn[6].addKeyListener(keyPress());

        btn[7].setBackground(new java.awt.Color(255, 255, 255));
        btn[7].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[7].setText("7");
        btn[7].addKeyListener(keyPress());

        btn[8].setBackground(new java.awt.Color(255, 255, 255));
        btn[8].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[8].setText("8");
        btn[8].addKeyListener(keyPress());

        btn[9].setBackground(new java.awt.Color(255, 255, 255));
        btn[9].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[9].setText("9");
        btn[9].addKeyListener(keyPress());

        btn[0].setBackground(new java.awt.Color(255, 255, 255));
        btn[0].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        btn[0].setText("0");
        btn[0].addKeyListener(keyPress());

        op[1].setBackground(new java.awt.Color(255, 255, 255));
        op[1].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[1].setText("-");
        op[1].addKeyListener(keyPress());

        op[2].setBackground(new java.awt.Color(255, 255, 255));
        op[2].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[2].setText("*");
        op[2].addKeyListener(keyPress());

        op[3].setBackground(new java.awt.Color(255, 255, 255));
        op[3].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[3].setText("/");
        op[3].addKeyListener(keyPress());

        op[4].setBackground(new java.awt.Color(255, 255, 255));
        op[4].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[4].setText("+");
        op[4].addKeyListener(keyPress());

        op[0].setBackground(new java.awt.Color(255, 255, 255));
        op[0].setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        op[0].setText("=");
        op[0].addKeyListener(keyPress());

        // This is auto-generated part for GUI when creating GUI using netbeans
        // The code positions various buttons on the calculator and also their
        // properties.
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(34, 34, 34)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                            .addComponent(btn[0], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                                .addComponent(op[1], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(43, 43, 43)
                                                .addComponent(op[2], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE))
                                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                                .addComponent(btn[7], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(43, 43, 43)
                                                .addComponent(btn[8], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE))
                                            .addGroup(layout.createSequentialGroup()
                                                .addComponent(btn[4], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(43, 43, 43)
                                                .addComponent(btn[5], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE))
                                            .addGroup(layout.createSequentialGroup()
                                                .addComponent(btn[1], javax.swing.GroupLayout.PREFERRED_SIZE, 105, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(44, 44, 44)
                                                .addComponent(btn[2], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE))
                                            .addComponent(op[4], javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.PREFERRED_SIZE, 255, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addGap(46, 46, 46)
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addComponent(btn[3], javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(btn[6], javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(btn[9], javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(op[3], javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                    .addComponent(clear, javax.swing.GroupLayout.PREFERRED_SIZE, 105, javax.swing.GroupLayout.PREFERRED_SIZE)))
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addGap(104, 104, 104)
                                .addComponent(op[0], javax.swing.GroupLayout.PREFERRED_SIZE, 106, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addGap(0, 19, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(displayBox)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(20, 20, 20)
                .addComponent(displayBox, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(clear, javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(29, 29, 29)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn[1], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[2], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[3], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(32, 32, 32)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn[4], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[5], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[6], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(37, 37, 37)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn[8], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[7], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn[9], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(30, 30, 30)
                .addComponent(btn[0], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(63, 63, 63)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(op[1], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(op[2], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(op[3], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(39, 39, 39)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(op[4], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(op[0], javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
    
}
