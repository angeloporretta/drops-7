<?php

// Plugin definition
$plugin = array(
    // Title and description of the plugin
    'title' => t('Custom Attributes'),
    'description' => t('Allows you you to set custom css attributes for the panel'),
    // Define a theme function for this plugin
    'render pane' => 'custom_attributes_style_render_pane',
    // We'll be using a template for rendering
    'hook theme' => array(
        'custom_attributes_style_pane' => array(
            'variables' => array(
                'content' => NULL,
                'title' => NULL,
                'style_attributes' => array(),
                'title_style' => array(),
                'settings' => NULL,
                'classes' => NULL,
                'variables' => NULL,
            ),
            'path' => drupal_get_path('module', 'panel_custom_style') . '/plugins/styles/custom_attributes',
            'template' => 'custom-attributes',
        ),
    ),
    // This defines the settings form for the plugin
    'pane settings form' => 'custom_attributes_style_settings_form',
);

/**
 * Settings form callback.
 */
function custom_attributes_style_settings_form($form, $form_state) {
    
    $theme = $GLOBALS['theme'];
  $instance = $theme;
  $file = drupal_get_path('theme', $theme) . '/' . $css_file;
    $style = '';
    $info = colorizer_get_info($theme, TRUE);
    if (file_exists($file)) {
      // Aggregate @imports recursively for each configured top level CSS file
      // without optimization. Aggregation and optimization will be
      // handled by drupal_build_css_cache() only.
      $style = drupal_load_stylesheet($file, FALSE);
    }
  $css_file = variable_get('colorizer_cssfile', '');
    $form['title-background'] = array(
        '#type' => 'textfield',
        '#title' => t('Title Background'),
        '#description' => t('Background colour for title text'),
        '#prefix' => '<div class="colorizer-form clearfix">',
        //'#required' => TRUE,
        '#default_value' => (isset($form['title-background'])) ? $form['title-background'] : '',
        '#attached' => array(
        // Add Farbtastic color picker.
        'library' => array(
          array('system', 'farbtastic'),
        ),
        // Add custom CSS.
        // 'css' => array(
        //   $base . '/css/colorizer_admin.css' => array(),
        // ),
        // Add custom JavaScript.
        'js' => array(
          drupal_get_path('module' , 'panel_custom_style') . '/style.js',
          array(
            'data' => array(
              'color' => array(
                'reference' => colorizer_get_palette($theme, $instance, TRUE),
                
              ),
              'gradients' => $info['gradients'],
              'css' => $style,
            ),
            'type' => 'setting',
          ),
        ),
      ),
    );
    $form['title-text'] = array(
        '#type' => 'textfield',
        '#title' => t('Title Text'),
        '#description' => t('Colour for the title text'),
        //'#options' => image_style_options(),
        '#default_value' => (isset($form['title-text'])) ? $form['title-text'] : '',
    );
    $form['title-border'] = array(
        '#type' => 'textfield',
        '#title' => t('Title Border'),
        '#description' => t('Border colour for the title text'),
        '#default_value' => (isset($form['title-border'])) ? $form['title-border'] : '',
    );
    $form['panel-background'] = array(
        '#type' => 'textfield',
        '#title' => t('Widget Background'),
        '#description' => t('Background colour for the widget'),
        '#default_value' => (isset($form['panel-background'])) ? $form['panel-background'] : '',
    );
    $form['panel-border'] = array(
        '#type' => 'textfield',
        '#title' => t('Widget Border'),
        '#description' => t('Border colour for the widget'),
        '#default_value' => (isset($form['panel-border'])) ? $form['panel-border'] : '',
    );
    // $form['panel-footer'] = array(
    //     '#type' => 'textfield',
    //     '#title' => t('Widget Footer'),
    //     '#description' => t('Background colour for the widget footer'),
    //     '#default_value' => (isset($form['panel-footer'])) ? $form['panel-footer'] : '',
    // );
    $form['border-width'] = array(
        '#type' => 'textfield',
        '#title' => t('Border Width'),
        '#description' => t('Border width for the pane in px'),
        '#default_value' => (isset($form['border-width'])) ? $form['border-width'] : '',
    );
    $form['border-radius'] = array(
        '#type' => 'textfield',
        '#title' => t('Border Radius'),
        '#description' => t('Border radius for the pane in px'),
        '#default_value' => (isset($form['border-radius'])) ? $form['border-radius'] : '',
    );
    $form['border-style'] = array(
        '#type' => 'select',
        '#title' => t('Border Style'),
        '#options' => array(
          'solid' => 'solid',
          'dashed' => 'dashed',
          'dotted' => 'dotted',
        ),
        '#description' => t('Border style for the pane'),
        '#default_value' => (isset($form['border-style'])) ? $form['border-style'] : '',
    );
    $form['panel-padding'] = array(
        '#type' => 'textfield',
        '#title' => t('Padding'),
        '#description' => t('Padding size for the pane in px'),
        '#default_value' => (isset($form['panel-padding'])) ? $form['panel-padding'] : '',
    );
    drupal_add_js(drupal_get_path('module' , 'panel_custom_style') . '/script.js');
    return $form;
}

/**
 * Render callback.
 */
function theme_custom_attributes_style_render_pane($vars) {
    $title_style = array();
    $panel_style = array();
    $footer_style = array();
    // add default values

    foreach($vars['settings'] as $key => $value) {
        if(isset($value) && !empty($value)) {
            switch($key) {
                case "title-background":
                    $title_style[] = "background-color:".$value;
                    break;
                case "title-text":
                    $title_style[] = "color:".$value;
                    break;
                case "title-border":
                    $title_style[] = "border-color:".$value;
                    break;
                case "panel-background":
                    $panel_style[] = "background-color:".$value;
                    break;
                case "panel-border":
                    $panel_style[] = "border-color:".$value;
                    break;
                case "panel-footer":
                    $footer_style[] = "background-color:".$value;
                    break;
                case "border-width":
                    $panel_style[] = "border-width:".$value."px";
                    break;
                case "border-radius":
                    $panel_style[] = "border-radius:".$value."px";
                    $panel_style[] = "-moz-border-radius:".$value."px";
                    $panel_style[] = "-webkit-border-radius:".$value."px";
                    break;
                case "border-style":
                    $panel_style[] = "border-style:".$value;
                    break;
                case "panel-padding":
                    $panel_style[] = "padding:".$value."px";
                    break;
            }
        } else {
            if ($key == 'title-background') {
                $title_style[] = "background-color:" . variable_get('style_default_color' , '');
            } else if ($key == 'title-text') {
                $title_style[] = "color:#ffffff";
            } else if ($key == 'panel-border') {
                $panel_style[] = "border-color:#c4bfbf";
            } else if ($key == 'border-width') {
                $panel_style[] = "border-width:1px";
            } else if ($key == 'panel-padding') {
                $panel_style[] = "padding:5px";
            }
        }
    }
    // add padding left 10 px for title
    $title_style[] = "padding-left:10px";
    $title_style[] = "margin-bottom:0px";
    $panel_style[] = "padding-left:10px";
    $style_attributes['style'] = implode(";", $panel_style);
    $style_attributes['style'] .= ";";

    $title_attributes['style'] = implode(";", $title_style);
    $title_attributes['style'] .= ";";

    // Get the absolute path of the original image from the context substitution
    /*$image_abs_path = ctools_context_keyword_substitute($vars['settings']['image'], array(), $vars['display']->context);

    $image_style = $vars['settings']['image_style'];

    if ($image_style == '') {
        // If no image style is selected, use the original image.
        $image_url = $image_abs_path;
    } else {
        // Image style is provided in the settings form.
        // We need to get the original image uri to return the URL for an image derivative.
        global $base_url;
        $files_rel_path = variable_get('file_public_path', conf_path() . '/files');
        $image_rel_path = str_replace($base_url . '/' . $files_rel_path, '', $image_abs_path);
        $image_uri = file_build_uri($image_rel_path);

        $image_style_url = image_style_url($image_style, $image_uri);

        $image_url = $image_style_url;
    }

    $style_attributes = array();
    $style_attributes['style'] = 'background-image: url(' . $image_url . ');';

    // Add our classes to the attrubutes array, if any defined
    if ($vars['settings']['class']) {
        $style_attributes['class'] = explode(' ', $vars['settings']['class']);
    }

    */
    $classes = '';
    $id = '';
    $content = $vars['content']->content;
    $title = $vars['content']->title;
    $settings = $vars['settings'];
    if (isset($vars['classes'])) {
      $classes = $vars['classes'];
    }
    if (isset($vars['id'])) {
      $id = $vars['id'];  
    }

    //return print_r($vars, true);
    return theme('custom_attributes_style_pane', array(
            'content' => $content,
            'title' => $title,
            'style_attributes' => $style_attributes,
            'title_style' => $title_attributes,
            'settings' => $settings,
            'classes' => $classes,
            'variables' => $vars,
        )
    );
}

