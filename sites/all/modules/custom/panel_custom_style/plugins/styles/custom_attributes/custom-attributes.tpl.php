<?php //echo "<pre>" . print_r($variables,true) . "</pre>"; ?>
<div class="<?php print $classes; ?>" <?php print $id; ?> <?php print drupal_attributes($style_attributes); ?>>
    <?php if ($title): ?>
        <h3<?php print $title_attributes; ?> <?php print drupal_attributes($title_style); ?>><?php print $title; ?></h3>
    <?php endif; ?>
    <div class="pane-content">
        <?php print render($content); ?>
    </div>
</div>
